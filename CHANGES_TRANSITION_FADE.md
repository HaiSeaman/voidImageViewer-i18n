# voidImageViewer 淡入淡出转场效果实现

## 概述

为 voidImageViewer 新增**淡入淡出（Fade）**图片切换转场效果，解决原版图片切换时的硬切卡顿感。转场通过 GDI 的 `AlphaBlend` API 实现，对现有绘制流水线改动最小。

## 功能特性

| 特性 | 说明 |
|------|------|
| 转场类型 | 淡入淡出（Fade） |
| 默认时长 | 300 毫秒 |
| 时长范围 | 50ms ~ 2000ms（9 档预设循环切换） |
| 刷新率 | 约 67fps（15ms 定时器间隔） |
| 计时方式 | 转场时长**不计入**幻灯片间隔 |
| 兼容性 | 与"动画时长"幻灯片模式、固定速率模式均兼容 |
| 持久化 | INI 文件 `transition_type` / `transition_duration` |
| 本地化 | 简体中文 + 英文 |

## 菜单路径

`查看（View）` → `转场效果（Transition）` →
- `无（None）` —— 关闭转场
- `淡入淡出（Fade）` —— 启用淡入淡出（默认）
- `时长（Duration）` —— 循环切换预设时长（50/100/200/300/500/800/1000/1500/2000ms）

## 技术实现原理

### 核心思路

采用**屏幕快照叠加**方案，对现有 WM_PAINT 绘制逻辑几乎零侵入：

1. **转场开始时**（`_viv_start_first_frame` 开头）：通过 `GetDC` + `CreateCompatibleBitmap` + `BitBlt` 截取当前屏幕（仍显示旧图）保存为 `_viv_transition_old_screen_bitmap`
2. **WM_PAINT 正常绘制新图**：完全复用原 BitBlt/StretchBlt 流水线
3. **WM_PAINT 末尾**：调用 `_viv_paint_transition_fade`，用 `AlphaBlend` 将旧屏幕快照以递减的 alpha 值叠加到新图上
4. **定时器驱动**：`VIV_ID_TRANSITION_TIMER`（15ms 间隔）触发 `InvalidateRect` 重绘，并检查是否到达时长终点
5. **转场结束**：释放快照位图，最终重绘一次无叠加的新图

### Alpha 混合公式

```
最终像素 = 新图 * (1 - alpha/255) + 旧图 * (alpha/255)
```
- 开始时 alpha=255：完全显示旧图
- 中点 alpha=128：新旧各半
- 结束时 alpha=0：完全显示新图

`BLENDFUNCTION` 参数：
- `BlendOp = AC_SRC_OVER`
- `SourceConstantAlpha = 当前 alpha`（常量混合，不依赖 per-pixel alpha）
- `AlphaFormat = 0`

## 修改的文件

### 1. `src/config.h`
新增两个配置变量声明：
```c
extern BYTE config_transition_type;     // 0 = none, 1 = fade
extern int  config_transition_duration;  // milliseconds, 50..2000
```

### 2. `src/config.c`
- 定义默认值：`config_transition_type = 1`（默认开启淡入淡出），`config_transition_duration = 300`
- INI 加载：`transition_type` / `transition_duration`（含 50~2000 范围钳位）
- INI 保存：对应字段

### 3. `src/viv.h`
新增枚举：
- `VIV_ID_TRANSITION_TIMER`（定时器 ID）
- `VIV_ID_VIEW_TRANSITION_NONE` / `VIV_ID_VIEW_TRANSITION_FADE` / `VIV_ID_VIEW_TRANSITION_DURATION`（菜单命令 ID）

### 4. `src/localization.h`
新增 6 个本地化 ID：
- `LOCALIZATION_ID_TRANSITION`、`LOCALIZATION_ID_TRANSITION_NONE`、`LOCALIZATION_ID_TRANSITION_FADE`
- `LOCALIZATION_ID_TRANSITION_DURATION`、`LOCALIZATION_ID_SET_TRANSITION_DURATION_CAPTION`、`LOCALIZATION_ID_TRANSITION_DURATION_STATIC`

### 5. `src/localization_en_us.h` / `src/localization_zh_cn.h`
对应添加 6 条中英文字符串。

### 6. `src/viv.c`（主要改动）

#### 新增全局状态变量
```c
static HBITMAP    _viv_transition_old_screen_bitmap;  // 旧屏幕快照
static int        _viv_transition_screen_wide;
static int        _viv_transition_screen_high;
static VIV_UINT64 _viv_transition_start_tick;
static BYTE       _viv_transition_active;
```

#### 新增菜单项
- 菜单句柄 `_VIV_MENU_VIEW_TRANSITION`
- 菜单数组：在 `Options...` 后插入 `Transition` 子菜单（含 None / Fade / Duration 三项）

#### 新增核心函数
| 函数 | 作用 |
|------|------|
| `_viv_transition_start()` | 截屏保存旧图快照，启动定时器 |
| `_viv_transition_end()` | 正常结束：KillTimer + 释放快照 + 最终重绘 |
| `_viv_transition_abort()` | 中断（快速切换时）：KillTimer + 释放快照 |
| `_viv_transition_get_alpha()` | 根据耗时计算当前 alpha 0~255 |
| `_viv_paint_transition_fade(HDC)` | WM_PAINT 末尾调用，AlphaBlend 叠加旧快照 |
| `_viv_set_transition_type(int)` | 设置转场类型 |
| `_viv_set_transition_duration()` | 循环切换预设时长 |

#### 改造 `_viv_start_first_frame`
在函数开头（InvalidateRect 之前）调用 `_viv_transition_start()`，确保截屏时屏幕仍是旧图。

#### 改造 WM_PAINT
在 `EndPaint` 之前调用 `_viv_paint_transition_fade(ps.hdc)`。

#### 新增 WM_TIMER 分支
`case VIV_ID_TRANSITION_TIMER:` 检查时长是否结束，结束则调用 `_viv_transition_end`，否则 `InvalidateRect` 触发下一帧。

#### 新增 WM_COMMAND 分支
处理 `VIV_ID_VIEW_TRANSITION_NONE` / `VIV_ID_VIEW_TRANSITION_FADE` / `VIV_ID_VIEW_TRANSITION_DURATION`。

#### 改造 `_viv_check_menus`
为 None / Fade 菜单项设置单选勾选状态。

### 7. `vs2026/voidImageViewer.vcxproj`
为 `Release|Win32` 配置的链接器依赖添加 `Msimg32.lib`（AlphaBlend 所需）。

## 边界情况处理

| 场景 | 处理方式 |
|------|----------|
| 快速连续切换图片 | `_viv_transition_start` 开头先调用 `_viv_transition_abort` 释放旧快照，再开始新转场 |
| 窗口最小化 / 尺寸为 0 | `GetClientRect` 返回 0 时直接跳过转场 |
| 截屏失败 | 各 GDI 调用均有 NULL 检查，失败则放弃转场 |
| 转场期间窗口尺寸变化 | AlphaBlend 会按快照原尺寸叠加，可能不完全覆盖，属可接受边界 |
| 与"动画时长"模式集成 | 转场在 `_viv_start_first_frame` 统一触发，所有切换路径自动支持 |
| 用户中途切换转场类型 | 仅影响下次切换，当前转场不中断 |

## 构建与验证

### 构建命令
```powershell
& "C:\Program Files\Microsoft Visual Studio\18\Community\MSBuild\Current\Bin\MSBuild.exe" `
    "d:\AI\trae\voidImageViewer-master\vs2026\voidImageViewer.sln" `
    /t:Build /p:Configuration=Release /p:Platform=Win32 /m /v:minimal
```

### 构建结果
- **配置**: Release | Win32 (x86)
- **输出**: `d:\AI\trae\voidImageViewer-master\vs2026\Release\voidImageViewer.exe`
- **大小**: 375,296 字节（约 366 KB）
- **构建时间**: 2026-07-18 16:35:13
- **退出码**: 0（成功）

### 自我审查清单

| 检查项 | 结果 |
|--------|------|
| 前置声明与实现签名一致 | ✅ 已修复 `_viv_paint_transition_fade` 签名 |
| localization enum 顺序与数组一致 | ✅ en_us / zh_cn 均已核对 |
| GDI 资源释放无泄漏 | ✅ 截屏位图在 end/abort 中均 DeleteObject |
| 定时器配对 KillTimer | ✅ end/abort 均调用 KillTimer |
| NULL 指针保护 | ✅ 所有 GDI 返回值均检查 |
| 未使用的旧变量已清除 | ✅ 无 `_viv_transition_old_frames` 残留 |
| Msimg32.lib 链接 | ✅ vcxproj 已添加 |
| 菜单单选互斥 | ✅ `_viv_check_menus` 使用 `MFT_RADIOCHECK` |
| 与动画时长模式兼容 | ✅ 转场在 `_viv_start_first_frame` 统一入口触发 |

## 使用说明

1. 运行 `voidImageViewer.exe`
2. 打开任意图片文件夹，开始浏览
3. 通过菜单 `查看 → 转场效果` 选择：
   - **淡入淡出**：开启转场（默认）
   - **无**：关闭转场
   - **时长**：重复点击循环切换 50/100/200/300/500/800/1000/1500/2000ms
4. 切换图片（下一张/上一张/幻灯片）时即可看到淡入淡出效果

## 性能说明

- 每帧转场开销：1 次 `AlphaBlend`（屏幕尺寸）
- 300ms 时长 / 15ms 间隔 ≈ 20 次重绘
- 现代 CPU 可轻松处理 1080p/4K 屏幕的 67fps AlphaBlend
- 截屏位图内存占用：屏幕宽 × 高 × 4 字节（如 1920×1080 ≈ 8MB，临时占用）

## 后续可扩展

当前架构支持轻松添加更多转场效果（滑动、推拉、百叶窗等），只需：
1. 扩展 `config_transition_type` 枚举
2. 实现对应的 `_viv_paint_transition_xxx` 函数
3. 在 WM_PAINT 末尾根据类型分发
