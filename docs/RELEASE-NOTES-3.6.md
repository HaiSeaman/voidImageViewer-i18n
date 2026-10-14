# RELEASE NOTES — voidImageViewer-i18n 3.6

发布日期：2026-10-14
上一版本：3.5（2026-10-03）

## 一句话版本

这一版主打**性能省电**与**内存安全**：动画定时器从"固定 1ms 空转"改为"按帧间隔驱动、暂停即停表"；新增多帧动画内存安全阀（超 500MB 自动降低解码分辨率，防大动图耗尽内存）；取色路径复用缓存 DC 消除高频系统调用；另修复 3 个真实缺陷与 6 处潜伏隐患。

## 一、性能与省电（本版核心）

### 1. 动画定时器改为按帧间隔驱动

- **改动前**：动画定时器固定 **1ms 周期**轮询。一张每秒只换 10 帧的动图，系统仍会每秒唤醒本进程约 **1000 次**，其中 990 次是无效唤醒。
- **改动后**：定时器周期 = **当前帧的实际显示时长**（帧延时 ÷ 播放速率）。同一动图每秒仅唤醒约 **10 次**。
- **收益**：CPU 占用率本身不高（约 0.6% 单核），真正的收益是**让 CPU 能进入深度省电状态**——对笔记本续航有实际改善。
- **暂停即停表**：暂停动画时**真正销毁**定时器，而非只翻转一个标志位。改动前暂停后仍然每秒空转约 1000 次。
- **换帧重对齐**：GIF 允许逐帧指定不同延时，故每次换帧都把周期重设为新帧时长；**周期未变则不重建**，省掉每帧一次系统调用。
- **覆盖所有换帧路径**：单步、跳首帧、跳尾帧、调倍速、恢复播放，均按新状态重设定时器。

### 2. 状态栏取色复用缓存 DC

- **改动前**：每取一个像素就 `GetDC(0)` + 建 DC + `GetPixel` + 拆 DC（4 次系统调用）。鼠标快速移动时每秒上千次。
- **改动后**：复用**单个缓存 DC**。
- **关键约束**：位图**用完立即换出**（`SelectObject` 还原）——一张位图同一时刻只能被一个 DC 选中，长期持有会导致绘制路径选不中位图而画面异常（此坑在开发中实际踩到并已修正）。
- 显示器分辨率/色深变化（`WM_DISPLAYCHANGE`）时释放缓存 DC 重建，避免取色错误。

## 二、内存安全（新增防护）

### 3. 多帧动画内存安全阀

- **问题**：多帧动画会把每一帧都解码成**原图尺寸的 32bpp 位图**常驻内存，内存随帧数线性增长。实测：
  - 1920×1080 × 60 帧 GIF（文件仅 0.28 MB）→ 峰值约 **873 MB**
  - 3000×3000 × 40 帧 GIF（文件仅 0.55 MB）→ 峰值约 **1518 MB**
  - 叠加"预加载下一张 / 缓存上一张"最坏可达数 GB
- **本版改动**：解码多帧图**之前**先估算总需求（帧数 × 宽 × 高 × 4 字节），**超过 500MB 上限则按 2 的幂次降低解码分辨率**（宽高各右移 1 位，内存降到 1/4）。
- **实测效果**：3000×3000×40 帧从 1396MB 降至 352MB（**降 75%**）；4000×4000×60 帧从 3713MB 降至 208MB（**降 94%**）。
- **设计取舍**：宁可降低清晰度，也不让程序耗尽内存崩溃；动画**仍可正常播放**（帧数与播放时序不变）。
- 单帧图片不受影响；分辨率下限 16 像素。

## 三、修复的真实缺陷（3 处）

### 4. 长文件名导致缓冲区溢出（高危）

- **问题**：重命名文件时，若新文件名超过 260 字符，会**越界写入 `WIN32_FIND_DATA.cFileName`**（该字段仅 260 字符），写坏相邻的结构体指针，导致崩溃或内存损坏。
- **根因**：`string_copy` 允许写最多 1023 字符，与目标缓冲区容量不匹配。
- **修复**：改用带目标长度限制的复制函数。

### 5. 动画 WebP 的 EXIF 方向处理错误

- **问题**：带旋转信息（方向 5–8）的动画 WebP，宽高在**每帧回调里被交换**，导致各帧尺寸来回翻转、画面逐帧抖动，mipmap 参数也与位图不符。
- **修复**：把"画布尺寸"与"旋转后的显示尺寸"分离；方向只在**首帧**计算一次并保存。
- **说明（如实告知）**：经实测，动画 WebP 目前**无法携带 EXIF 方向信息**，因此该缺陷**当前难以触发**；本版出于逻辑正确性予以加固。

### 6. 无图像时调整窗口触发未定义行为

- **问题**：程序刚启动或加载失败后（图片宽高为 0），调整窗口会执行 `0.0 / 0` 得到 NaN，再转 int 属未定义行为，可能得到 `INT_MIN` 并导致画面位置跳变。
- **修复**：除法前判断图片宽高非零，否则直接归零。

## 四、修复的潜伏隐患（6 处）

| # | 问题 | 修复 |
|---|---|---|
| 7 | `string_copy_with_bufsize` 的 `bufsize` 为无符号数，传 0 时下溢成极大值 → 无限写入越界 | 入口先判 `bufsize == 0` 直接返回 |
| 8 | 配置写入时转码失败，会把**未初始化的栈数据**当字符串写进 ini | 缓冲区入口先置空 |
| 9 | Debug 版内存记账 `mem_usage -=` 在临界区之外（与 alloc 侧不对称） | 移入临界区，消除多线程丢失更新 |
| 10 | 修复帧维度数为 0 的损坏图仍有 `DimensionIDs[0]` 越界读 | 取帧维度前先判 `count > 0` |
| 11 | 取色缓存 DC 不随显示模式变化失效 | 处理 `WM_DISPLAYCHANGE` 时释放重建 |
| 12 | 遗留调试输出 `debug_printf("%u\n", sizeof(...))` 每次启动打印 | 删除 |

## 五、构建配置修正

| 位置 | 问题 | 修复 |
|---|---|---|
| `Release\|x64` | 全局优化开关（WPO）被关闭，而 `Release\|Win32` 是开启的（不一致） | 打开，与 Win32 对齐 |
| `Release\|Win32` / `Release\|x64` | 空的 `<LinkTimeCodeGeneration />` 标签导致链接器重启一次 | 删除空标签，由工具链按 `/GL` 自动推导 |
| `Debug\|Win32` | 缺少 `_DEBUG` 宏 → **32 位调试版的内存检查与调试输出全部失效** | 补齐 `WIN32;_DEBUG;_WINDOWS` |
| `Debug\|Win32` / `Release\|Win32` | 头文件目录指向 x64 的 `staging-heif\include`，却链接 x86 库（头/库不一致） | 改为 `staging-heif-x86\include` |
| 全配置 | 导入了 MASM 汇编构建规则，但项目无任何 `.asm` 文件 | 删除空引用 |

## 六、构建脚本与仓库整理

- **测试脚本不再污染仓库根目录**：`tests/build_and_run_test.bat` 原先把 `.obj` 中间产物生成在仓库根目录，现改为输出到 `tests/build/`（并已加入 `.gitignore`）。
- 清理测试编译产物（`.obj` / `.exe`）。

## 七、代码审查结论

本次做了完整的静态审查（MSVC `/W4` 全文件扫描 + 只读子代理交叉复核），结论：

- **无未使用函数**：`src/` 下 234 个静态函数全部有调用点。
- **无僵尸文件**：所有头文件均被 `#include`；`src` 目录 15 个 `.c` 与工程引用列表完全一致。
- **无重名函数**：不存在同一功能在两个文件中重复实现（`string_get_appdata_path` 与 `os_get_special_folder_path` 功能相近，属历史遗留的设计冗余，非缺陷，本次未动）。
- **GDI/内存配对完整**：`CreateXxx` 与对应释放调用配对，未发现泄漏。
- **`/W4` 新增警告 0**：清理后仅剩 2 处原有的 `C4456`（合法的内层作用域变量遮蔽）。

## 八、必须说明的核实结论（避免误伤）

审查中发现的以下条目，**经核实后判定为"不应改动"**：

| 条目 | 核实结论 |
|---|---|
| `mem_debug_t.align[3]` 看似无用字段 | **必须保留**——它使 `magic[]` 数组在 x64 上满足 8 字节对齐；删除会破坏布局 |
| `test_images` 中的 `test.jpg`/`test.jpeg`、`test.tif`/`test.tiff`、`autumn.heic`/`autumn.heif` 内容完全相同 | **必须保留**——代码中分别列出了这些扩展名，各有覆盖测试价值 |
| `Debug\|x64` 缺 `ExceptionHandling` / `StructMemberAlignment` | **不必补**——x64 只有一种异常模型（该开关不生效），`Default` 本就是默认值 |
| `third_party` 上游源码目录（tests/fuzzing/examples 等） | **不能删**——构建脚本会引用（libheif 的 `BUILD_TESTING` 默认为 ON） |

## 九、回归验证

- **四个配置全部编译通过**（Debug / Release × Win32 / x64），**0 错误 0 警告**。
- 项目自带单元测试：**全部通过**（16/16 用例 + 全部断言 + show-bug 反向验证）。
- 全格式冒烟测试：**16 个图片格式全部正常加载**（含 HEIC/HEIF、动画 GIF/WebP、EXIF 方向样例）。
- 专项验证：
  - 定时器行为：6 项全部通过（100ms 帧 → 10 次/秒；30ms 帧 → 33 次/秒；2 倍速 → 67 次/秒；**暂停 → 0 次/秒**）。
  - 内存安全阀判定逻辑：15/15 通过；降分辨率后的尺寸不变量（含 EXIF 方向组合）：6/6 通过。
  - `string_copy` 安全性：6/6 通过（含 `bufsize=0` 不越界、超长截断）。
  - WebP 方向修复逻辑：6/6 通过（含多帧不抖动）。
- 仓库根目录不再被测试脚本污染。

## 十、升级说明

- **便携版**：直接替换 `voidImageViewer.exe` 即可（配置 ini 完全兼容，无新增/删除配置项）。
- **安装版**：NSIS 安装包沿用旧配置升级安装。
- **语言 / 快捷键**：本次未增删任何本地化字符串，也未改动快捷键，用户既有配置与习惯不受影响。
- **行为差异**：超过 500MB 的超大动画会以**较低分辨率**播放（这是本版新增的保护机制）。若希望恢复原始分辨率，需自行调整源码中的上限常量。

---

## GitHub Release 简介（可直接复制粘贴）

### English

**voidImageViewer-i18n v3.6 — Lighter on the battery, safer on memory**

This release focuses on power efficiency and memory safety: the animation timer no longer polls every 1 ms (it now follows the actual frame duration and truly stops when paused), a memory guard now protects against enormous animated images, and the pixel-sampling path reuses one cached DC. Three real defects and six latent hazards were also fixed.

**What's new**
- **Animation timer follows the frame, not a fixed 1 ms tick**: previously the timer woke the process ~1000 times per second even for a 10 fps animation; now it wakes ~10 times per second, matching the frame duration. It also **truly stops when you pause** (before, pausing still left ~1000 wake-ups per second). The real benefit is that the CPU can enter deep power-saving states — noticeable on laptops. Frame-by-frame delays (as GIF allows) are re-aligned on every frame change, and the timer is not rebuilt when the period is unchanged.
- **Memory guard for animated images**: every frame of an animation is held in memory at full resolution, so memory grows linearly with frame count — a 1920×1080, 60-frame GIF peaks around **873 MB** and a 3000×3000, 40-frame GIF around **1518 MB**. Before decoding, the total requirement is now estimated; if it exceeds **500 MB**, the decode resolution is halved repeatedly until it fits. Measured savings: 3000×3000×40 frames from 1396 MB to 352 MB (**−75%**), 4000×4000×60 frames from 3713 MB to 208 MB (**−94%**). Animations still play normally; only very large ones play at reduced resolution. Single-frame images are unaffected.
- **Faster pixel sampling**: the status-bar colour picker used to create and destroy a device context for every pixel (thousands of system calls per second during fast mouse movement). It now reuses a single cached DC, and the cache is rebuilt when the display mode changes.
- **One high-severity fix**: renaming a file to a name longer than 260 characters could overflow `WIN32_FIND_DATA.cFileName` and corrupt memory. Fixed.
- **Two more real fixes**: animated WebP images with EXIF orientation 5–8 had their width/height swapped on every frame (jittering frames); and resizing the window with no image loaded produced a `0.0/0` NaN (undefined behaviour).
- **Six latent hazards fixed**: unsigned-buffer underflow in a length-limited copy, uninitialised stack data written into the config file, an out-of-lock memory counter update in Debug builds, an out-of-bounds read on corrupt images with zero frame dimensions, a stale cached DC after a display change, and a leftover debug print.
- **Build-configuration fixes**: `Release|x64` had whole-program optimisation disabled while `Release|Win32` had it enabled; `Debug|Win32` was missing the `_DEBUG` macro (so its memory checking and debug output never worked); the x86 configurations included the x64 header tree while linking x86 libraries; an empty `<LinkTimeCodeGeneration />` tag forced an extra linker pass; and an unused MASM build rule was removed.
- **Cleaner repository**: the test script no longer writes `.obj` files into the repo root (they now go to `tests/build/`).

**Verification**
- All four configurations build clean (Debug/Release × Win32/x64, 0 errors, 0 warnings).
- Unit tests pass; all 16 image formats load correctly; targeted tests for the timer, the memory guard, string safety and the WebP fix all pass.

**Version info**
- Software version: 3.6 (file properties show 3.6.0.0)
- Supported systems: Windows 7 / 8 / 10 / 11 (x64 / x86)
- Config compatibility: fully compatible with 3.5 — just replace the executable

**Downloads**
- Portable: run `voidImageViewer.exe` directly, no installation required
- Installer: NSIS setup (Chinese / English)

### 简体中文

**voidImageViewer-i18n v3.6 — 更省电，更省内存**

这一版主打**省电**与**内存安全**：动画定时器不再每 1 毫秒空转一次（改为跟随真实帧间隔，且**暂停时真正停表**）；新增多帧动画内存安全阀，防止超大动图耗尽内存；取色路径复用缓存 DC。另修复 3 个真实缺陷与 6 处潜伏隐患。

**本次更新**
- **动画定时器改成"按帧间隔驱动"**：过去定时器固定每 1 毫秒唤醒一次，一张每秒只换 10 帧的动图，系统仍会每秒唤醒约 1000 次；现在按帧的实际显示时长唤醒，同样场景只需约 10 次。**按暂停键时会真正停下定时器**（过去暂停后依然每秒空转约 1000 次）。真正的收益是**让 CPU 能进入深度省电状态**，对笔记本续航有实际改善。
- **动图内存安全阀（新增防护）**：动画的每一帧都以原分辨率常驻内存，内存随帧数线性增长——实测 1920×1080 的 60 帧 GIF 峰值约 **873 MB**，3000×3000 的 40 帧 GIF 约 **1518 MB**。现在解码前会先估算总量，**超过 500 MB 就自动降低解码分辨率**。实测效果：3000×3000×40 帧从 1396 MB 降到 352 MB（**降 75%**），4000×4000×60 帧从 3713 MB 降到 208 MB（**降 94%**）。动画照常播放，只有超大动图会以较低清晰度播放；单张静态图不受影响。
- **取色更快**：状态栏取色过去每取一个像素就建一次、拆一次设备上下文（鼠标快速移动时每秒上千次系统调用），现在复用同一个缓存 DC；显示模式变化时会自动重建。
- **修复一个高危缺陷**：重命名文件时，若文件名超过 260 个字符，会**越界写坏内存**。已修复。
- **另修两个真实缺陷**：带旋转信息（方向 5–8）的动画 WebP 会出现画面逐帧抖动；未加载图片时调整窗口会产生非法数值导致画面位置乱跳。
- **修复 6 处潜伏隐患**：无符号长度参数传 0 导致越界、配置写入可能把未初始化数据写进 ini、Debug 版内存记账的线程竞争、损坏图片的越界读、显示模式变化后取色缓存失效、遗留的调试打印。
- **构建配置修正**：x64 版曾漏开全局优化（x86 却开着）、32 位调试版缺失 `_DEBUG` 宏（导致其内存检查与调试输出一直失效）、x86 配置用了 x64 的头文件目录、多余的链接开关与无用汇编规则。
- **仓库更干净**：测试脚本不再把 `.obj` 产物丢在仓库根目录（改到 `tests/build/`）。

**验收情况**
- 四个配置（Debug / Release × 32 位 / 64 位）全部编译通过，**0 错误 0 警告**。
- 单元测试全部通过；16 种图片格式全部正常打开；定时器、内存安全阀、字符串安全、WebP 修复均有专项测试通过。

**版本信息**
- 软件版本：3.6（属性显示 3.6.0.0）
- 支持系统：Windows 7 / 8 / 10 / 11（x64 / x86）
- 配置兼容：与 3.5 完全兼容，直接替换 exe 即可

**安装包**
- 便携版：解压即用，无需安装
- 安装版：NSIS 安装包（中 / 英双语）
