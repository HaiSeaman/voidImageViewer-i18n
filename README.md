# void Image Viewer（多语言 & 汉化增强版）

> 一款专为 Windows 打造的轻量级、极速看图软件，支持 10 种语言无缝切换、默认 1:1 像素级放缩与动画 GIF / WebP 流畅播放。
> 本项目基于 [voidtools/voidImageViewer](https://github.com/voidtools/voidImageViewer) 进行沉浸式体验增强与多语言扩展。
> **当前版本：v3.0**

[下载最新版](#下载) ｜ [新增特性](#相查原版的主要改动) ｜ [功能特性](#功能特性) ｜ [使用说明](#使用说明) ｜ [从源码构建](#从源码构建) ｜ [已知问题](#已知问题与限制)

---

## 关于本分支

首先向原作者 **voidtools / David Carpenter** 致以最诚挚的敬意。`voidImageViewer` 继承了与 [Everything](https://www.voidtools.com/) 相同的设计哲学——极致轻量、启动毫秒级响应、内存占用低。

本分支在此基础上进行了全面增强，新增 **10 种国际语言支持**、**默认 1:1 原始大小看图与配置持久化**，并加入了淡入淡出转场等沉浸式体验优化。

### 相较原版的主要改动

| 改动模块 | 说明 |
| --- | --- |
| **多语言支持 (i18n)** | 内置 10 种语言（中文、英语、日语、韩语、法语、德语、西班牙语、葡萄牙语、意大利语、阿拉伯语），支持系统语言自动识别与菜单即时切换（无需重启），阿拉伯语自动支持 RTL 布局。 |
| **默认 1:1 原始缩放** | 突破原版窗口适应缩放逻辑，打开图片默认保持 **1:1 (100%) 原始像素大小**，并在 `voidImageViewer.ini` 中持久化保存软件默认设置。 |
| **幻灯片淡入淡出转场** | 为幻灯片自动切换增加平滑的淡入淡出过渡动画，可在「视图 → 转场效果」中开启，并支持自定义时长（50–2000 ms）。 |
| **无边框沉浸式看图** | 默认隐藏标题栏、菜单栏、状态栏与粗边框，改用右键菜单与快捷键操控，最大化显示区域。 |
| **窗口贴合与标题配置** | 支持窗口根据图片尺寸自动贴合消除白边，标题栏支持显示完整路径、仅文件名或无标题栏。 |
| **中文文档与使用规范** | 提供完整的中文技术文档、配置指南与构建说明。 |

---

## 功能特性

### 多语言与本地化

- **10 种语言无缝切换**：
  - 简体中文 (`Simplified Chinese`)
  - 英语 (`English`)
  - 日语 (`Japanese`)
  - 韩语 (`Korean`)
  - 法语 (`French`)
  - 德语 (`German`)
  - 西班牙语 (`Spanish`)
  - 葡萄牙语 (`Portuguese`)
  - 意大利语 (`Italian`)
  - 阿拉伯语 (`Arabic` - 支持 RTL 从右往左镜像布局)
- **智能语言识别**：首次启动自动识别 Windows 系统语言，若未在支持列表内则自动回退至英语。
- **动态重绘**：切换语言后无需重启，菜单栏、右键菜单和对话框即时完成更新。

### 图像格式与解码

- **当前支持的格式**：
  - **基础常见格式**：JPEG/JPG、PNG、BMP、TIFF/TIF、ICO（GDI+ / Win32 原生）。
  - **WebP**：静态 WebP 与多帧动画 WebP（内置轻量级 `libwebp` 解码引擎）。
  - **动画 GIF**：逐帧播放（GDI+ 原生）。
  - **HEIC/HEIF**：内置 `libheif` + `libde265` 开源解码引擎（MIT 许可），开箱即用，**无需**安装系统的"HEIF 图像扩展"组件；支持 iPhone 等设备拍摄的 HEVC 照片与 EXIF 方向自动旋转。
- **超大图渲染**：支持高分辨率图像渲染与平移，内置安全算术库防范内存乘法溢出。
- **说明**：AVIF、APNG、TGA、WMF/EMF、CUR/ANI 等格式的解码器尚未实现，已在文件选择器与 Everything 搜索过滤器中同步移除，避免出现"列得出、打不开"的情况。

#### 图像格式支持一览表

| 格式分类 | 扩展名 (Extension) | 解码引擎 / 实现路径 | 渲染特性与优势 |
| :--- | :--- | :--- | :--- |
| **常见标准格式** | `.jpg`, `.jpeg`, `.png`, `.bmp`, `.tif`, `.tiff`, `.ico` | GDI+ / Win32 原生 | 支持 Exif 自动旋转、 Alpha 透明通道与高清像素呈现 |
| **动画 GIF** | `.gif` | GDI+ 帧解码 | 逐帧播放动画 GIF，支持播放控制 |
| **WebP** | `.webp` | 内置 `libwebp` 开源解码引擎 | 支持静态 WebP 及多帧动画 WebP 高流畅度播放 |
| **HEIC/HEIF** | `.heic`, `.heif` | 内置 `libheif` + `libde265` 解码引擎（WIC 可用时优先走系统组件） | 无需系统 HEIF 扩展即可打开 iPhone 等设备拍摄的 HEVC 照片 |

### 看图与缩放

- **1:1 实际大小 (默认)** / **最佳适应** / **填充窗口** / **允许缩小** / **保持纵横比** 多种放缩模式。
- **平移与扫描 (Pan & Scan)**：八方向微调、居中显示、画布与窗口按比例调整。
- **高性能 Mipmap**：对缩小显示的图像预生成多级缩放图，解决像素交错抗锯齿并提升渲染效能。
- **平滑缩放**：支持鼠标滚轮微调与热键平滑放大/缩小。

### 动画与幻灯片

- **动画控制**：播放/暂停、逐帧单步、首帧/尾帧跳转、动画播放速率调节（加速/减速/重置）。
- **幻灯片效果**：支持 250 ms ~ 60 s 的自定义播放间隔，或按动画固有帧率自动播放。
- **淡入淡出转场**：淡入淡出过渡动画效果，支持自定义 50 ms–2000 ms 的转场时间。
- **系统防休眠**：播放幻灯片或动图时自动阻止屏幕保护程序启动与系统进入休眠。

### 导航管理与 Everything 集成

- **智能预加载**：支持“预加载下一张”与“缓存上一张”，实现图片切换零卡顿。
- **灵活排序**：支持按文件名、文件大小、修改时间、创建时间、完整路径进行升序/降序及**自然排序 (Natural Sort)**。
- **Everything 联动**：可直接调取 [Everything](https://www.voidtools.com/) 的本地全局搜索结果作为图片播放列表。

### 文件与编辑操作

- **文件管理**：支持打开单文件/文件夹、拖拽加载、快捷剪切/复制/粘贴、移动/复制到指定目录。
- **文本与画质处理**：支持一键复制图像到剪贴板、复制文件路径、EXIF 方向 (`System.Photo.Orientation`) 自动旋转、无损旋转。
- **壁纸与打印**：支持设为桌面壁纸、调用系统打印对话框。

### 界面与快捷键自定义

- **按键映射**：所有键盘快捷键均可自定义添加、修饰与删除。
- **鼠标热键**：左键、右键、滚轮、Ctrl+滚轮、侧键 (XButton) 等均可自由指派功能（如拖拽平移、滚轮缩放、切换图片等）。
- **配置文件便携化**：配置写入 `voidImageViewer.ini`，可灵活保存在程序当前目录或 `%APPDATA%`，支持多实例运行。

---

## 下载

- **发行版下载**：请访问 GitHub [Releases](../../releases) 页面下载最新构建版本。
- **官方原版资源**：
  - Voidtools 官网论坛：[https://www.voidtools.com/forum/viewtopic.php?t=5623](https://www.voidtools.com/forum/viewtopic.php?t=5623)
  - Voidtools GitHub 仓库：[https://github.com/voidtools/voidImageViewer](https://github.com/voidtools/voidImageViewer)

**v3.0 发布文件**：提供 32 位 (`x86`) 与 64 位 (`x64`) 免安装绿色便携版压缩包，解压即用；同时提供标准 NSIS 安装包（中/英双语）。

| 类型 | 文件 |
| --- | --- |
| 便携版 x64 | `voidImageViewer-3.0.x64.zip` |
| 便携版 x86 | `voidImageViewer-3.0.x86.zip` |
| 安装包 x64 中文 | `voidImageViewer-3.0.x64.zh-CN-Setup.exe` |
| 安装包 x64 英文 | `voidImageViewer-3.0.x64.en-US-Setup.exe` |
| 安装包 x86 中文 | `voidImageViewer-3.0.x86.zh-CN-Setup.exe` |
| 安装包 x86 英文 | `voidImageViewer-3.0.x86.en-US-Setup.exe` |

---

## 使用说明

### 快速上手

1. 双击 `voidImageViewer.exe` 打开软件，或直接将图片文件拖入软件窗口中。
2. **单击鼠标右键** 呼出功能主菜单（默认开启无边框沉浸模式）。
3. 滚动鼠标滚轮或按键盘 `↑` / `↓` 切换上一张/下一张图片。
4. 按下 `F` 键或通过右键菜单进入全屏模式。

### 切换语言

在窗口内右键点击，选择 **「查看 (View)」→「语言 (Language)」**，点击所需的语言即可瞬间完成界面语言切换。

### 命令行参数

在命令行窗口执行 `voidImageViewer.exe /?` 可调阅帮助：

```bash
用法：
voidImageViewer.exe [/开关] [文件名...]

常见开关：
/slideshow      启动后直接播放幻灯片。
/fullscreen     以全屏模式启动。
/maximized      以窗口最大化启动。
/window         以普通窗口模式启动。
/ontop          置顶显示窗口。
/minimal        无边框模式启动。
/compact        紧凑边框模式启动。
/x <x> /y <y> /width <w> /height <h>  自定义窗口初始坐标与宽高。
/rate <ms>      设置幻灯片放映间隔毫秒数。
/name           按文件名排序。
/size           按文件大小排序。
/dm             按修改时间排序。
/shuffle        随机打乱播放列表。
/appdata        配置强行写入 AppData 目录。
/noappdata      配置强行写入 EXE 所在目录（便携模式）。
```

*注：本分支亦完美兼容使用包含 `-` 前缀的参数（如 `-fullscreen`）。*

---

## 配置说明

软件相关设置均存储于 `voidImageViewer.ini` 文件中。常见核心配置参数项如下：

| 配置键名 | 说明 | 默认值 |
| --- | --- | --- |
| `language` | 界面语言（`-1` 为自动识别，`0`=英语，`1`=中文...） | `-1` |
| `auto_zoom` | 是否启用自动缩放设置 | `1` |
| `auto_zoom_type` | 自动缩放类型（`0`=适应窗口，`1`=100%/1:1原始大小） | `1` |
| `fit_window_to_image` | 窗口根据图片尺寸自动贴合调节大小 | `1` |
| `show_caption` | 显示窗口标题栏 | `0` (隐藏) |
| `show_menu` | 显示主菜单栏 | `0` (隐藏) |
| `show_status` | 显示底部状态栏 | `0` (隐藏) |
| `transition_type` | 幻灯片转场效果（`0`=无，`1`=淡入淡出） | `1` |
| `transition_duration` | 淡入淡出转场效果时长（毫秒，50–2000） | `300` |
| `title_bar_format` | 标题栏显示格式（`0`=完整路径，`1`=仅文件名，`2`=不显示） | `1` |
| `preload_next` | 开启下一张图片预加载 | `1` |
| `cache_last` | 开启上一张图片缓存 | `1` |

---

## 从源码构建

本项目采用标准 C 语言编写，依赖 Win32 API。

### 开发环境要求
- **编译器**：Microsoft Visual Studio 2026 或更新版本（需安装 C++ 桌面开发工作负载；工程工具集为 `v145`）
- **构建工具**：MSBuild
- **系统支持**：Windows 7 / 8 / 10 / 11

### 编译步骤

1. 克隆代码库：
   ```bash
   git clone https://github.com/your-username/voidImageViewer.git
   cd voidImageViewer
   ```
2. 使用 Visual Studio 打开 `vs2026/voidImageViewer.sln`。
3. 选择构建目标架构（`x64` 或 `x86`）以及配置类型（`Release`）。
4. 点击 **生成 -> 生成解决方案**，编译生成的可执行文件存放在 `vs2026/voidImageViewer/x64/Release/`（x64）或 `vs2026/voidImageViewer/Release/`（x86）目录下。

你也可以在命令行中运行构建脚本（脚本会自动通过 vswhere 定位 VS 工具链）：
```cmd
build_vs2019.bat
```

---

## 许可证与致谢

- **开源许可证**：本项目采用 [MIT 许可证](LICENSE)。
- **原作者**：[voidtools / David Carpenter](https://www.voidtools.com/)。
- **第三方解码库**：内置 [libwebp](https://chromium.googlesource.com/webm/libwebp) 以提供完整的 WebP 解码能力。
