# void Image Viewer（汉化增强版）

> 一款专为 Windows 打造的轻量级、极速看图软件，支持动画 GIF / WebP 播放。
> 本项目是基于 [voidtools/voidImageViewer](https://github.com/voidtools/voidImageViewer) 的简体中文汉化与沉浸式体验增强分支。

[下载最新版](#下载) ｜ [功能特性](#功能特性) ｜ [使用说明](#使用说明) ｜ [从源码构建](#从源码构建) ｜ [已知问题](#已知问题与限制)

---

## 关于本分支

首先要向原作者 **voidtools / David Carpenter** 表达最诚挚的感谢。`voidImageViewer` 秉承了与 [Everything](https://www.voidtools.com/) 相同的设计哲学——极致简洁、流畅高效。本分支在此基础上，让中文用户能用得更顺手、看得更舒服。

### 相较原版的主要改动

| 改动 | 说明 |
| --- | --- |
| **界面汉化** | 完成了菜单、对话框、提示信息的简体中文本地化。 |
| **幻灯片淡入淡出转场** | 为幻灯片自动切换增加了淡入淡出过渡动画，过渡更平滑流畅；可在「视图 → 转场效果」中开关，并自定义时长（50–2000 毫秒）。 |
| **无边框沉浸式看图** | 默认隐藏系统标题栏、菜单栏、状态栏、工具栏与粗边框，改用右键菜单操作，最大化看图视野。 |
| **窗口自动贴合图片** | 窗口自动贴合图片实际显示大小，消除多余白边。 |
| **标题栏格式可选** | 支持完整路径 / 仅文件名 / 无标题栏三种显示方式。 |
| **中文文档** | 提供中文版 `README` 与使用说明，方便中文用户快速上手。 |

核心看图逻辑与原项目保持一致，未做破坏性修改。

---

## 功能特性

### 图片格式支持

打开并显示以下格式，力求越快越好：

| 格式 | 说明 |
| --- | --- |
| **BMP** | 位图 |
| **GIF** | 含动画 GIF，逐帧准确播放 |
| **ICO** | 图标文件 |
| **JPEG / JPG** | JPEG 图像 |
| **PNG** | 便携式网络图形 |
| **TIF / TIFF** | TIFF 图像 |
| **WebP** | 含动画 WebP（内置 libwebp 解码） |

### 看图与缩放

- **1:1 实际大小** / **最佳适应** / **填充窗口** / **允许缩小** / **保持纵横比** 多种显示模式。
- **平移和扫描（Pan & Scan）**：增大/减小尺寸，调整宽高，八方向移动，居中，重置。
- **缩放**：放大、缩小、重置；支持鼠标滚轮缩放。
- **Mipmap 支持**：为缩小显示预生成多级缩放图，加快大图缩放渲染。
- 支持显示大于 65536×65536 的超大图（1.0.0.14 修复）。

### 动画播放

- 准确播放动画 GIF 与动画 WebP。
- **播放 / 暂停**、**逐帧**（下一帧 / 上一帧）、跳到**第一帧 / 最后一帧**。
- **短/中/长距离向前/向后跳转**。
- **动画速率调节**：加速 / 减速 / 重置。
- 可设置「在幻灯片中至少播放一次动画」。

### 幻灯片放映

- 速率可调：250 毫秒 ~ 60 秒，或自定义速率（毫秒/秒/分钟）。
- 可使用动画图像自身的循环时长作为幻灯片间隔（静态图回退到设定速率）。
- **淡入淡出转场效果**（本分支增强），可自定义转场时长。
- 播放 / 暂停 / 停止；随机播放；防止屏幕保护与系统休眠。

### 导航管理

- 上一张 / 下一张 / 首页 / 末页。
- 排序：名称 / 大小 / 修改日期 / 创建日期 / 完整路径，升序或降序（含自然排序）。
- **随机播放**、**跳转到列表**。
- **预加载下一张**、**缓存上一张**，切换更流畅。
- 支持 **Everything 搜索**集成（需安装 [Everything](https://www.voidtools.com/)）：可直接用 Everything 搜索结果打开/添加图片。

### 文件与编辑操作

- 打开文件 / 打开文件夹 / 添加文件 / 添加文件夹。
- 打开文件位置（在资源管理器中显示）、查看属性。
- 剪切、复制、粘贴、**复制文件名**、**复制图像**。
- 复制到文件夹 / 移动到文件夹。
- 顺时针 / 逆时针旋转（仅在内存中旋转）。
- 重命名、删除（移至回收站 / 永久删除）。
- 打印、预览、设为桌面壁纸。

### 窗口与界面

- **全屏模式**与窗口模式，可一键切换。
- **无边框沉浸模式**（本分支默认）：隐藏标题栏、菜单、状态栏、工具栏、粗边框。
- 三种界面预设：最小 / 紧凑 / 正常。
- 窗口大小预设：50% / 100% / 200% / 自动适应。
- 窗口背景色与全屏背景色可分别自定义。
- **窗口置顶**：总是 / 播放时 / 从不。
- 全屏时自动隐藏鼠标指针。

### 高度可定制

- **键盘快捷键**完全可自定义：为每个命令添加/编辑/删除快捷键。
- **鼠标操作可定制**：左键、右键、滚轮、Ctrl+滚轮、侧键（XButton）均可指派不同动作。
  - 可选动作：滚动、播放/暂停幻灯片、播放/暂停动画、放大、下一张/上一张、1:1 滚动、移动窗口、上下文菜单、缩放等。
- 设置保存为 `voidImageViewer.ini`，可存于程序目录或 `%APPDATA%\voidImageViewer`（便携友好）。
- 支持单实例或多实例运行。

### 色彩与元数据

- ICM 色彩管理。
- 支持 EXIF 方向（`System.Photo.Orientation`）自动旋转。
- 状态栏可显示像素信息、位置、缩放、宽高比、动画速率、幻灯片间隔。

---

## 下载

- 本分支发布页：（请在此填写你的 GitHub Releases 地址）
- 原版发布页：https://github.com/voidtools/voidImageViewer/releases
- 原版论坛帖：https://www.voidtools.com/forum/viewtopic.php?t=5623

提供 32 位（x86）与 64 位（x64）独立 exe，无需安装即可运行；亦可使用 NSIS 安装程序。

---

## 使用说明

### 快速上手

1. 双击 `voidImageViewer.exe` 启动，或将图片直接拖入窗口。
2. **右键单击**呼出全部菜单（本分支默认无边框，主要靠右键菜单操作）。
3. 上下方向键或滚轮浏览上一张/下一张（取决于鼠标设置）。
4. 按 `F` 或在菜单中选择「全屏」进入全屏看图。

### 命令行选项

在命令提示符中运行 `voidImageViewer.exe /?` 可查看完整帮助：

```
用法：
voidImageViewer.exe [/开关] [文件名(s)]

开关：
/slideshow      开始幻灯片放映。
/fullscreen     开始全屏。
/maximized      开始最大化。
/window         开始窗口模式。
/ontop          置顶显示。
/minimal        无边框窗口。
/compact        带边框窗口。
/x <x> /y <y> /width <width> /height <height>
                设置窗口位置和大小。
/rate <rate>    设置幻灯片间隔（毫秒）。
/name           按名称排序。
/path           按完整路径排序。
/size           按大小排序。
/dm             按修改日期排序。
/dc             按创建日期排序。
/ascending      升序排序。
/descending     降序排序。
/shuffle        随机播放列表。
/<bmp|gif|ico|jpeg|jpg|png|tif|tiff|webp>
                安装文件关联。
/no<bmp|gif|ico|jpeg|jpg|png|tif|tiff|webp>
                卸载文件关联。
/appdata        设置保存到 AppData。
/noappdata      设置保存到 exe 所在目录。
/startmenu      添加开始菜单快捷方式。
/nostartmenu    移除开始菜单快捷方式。
/install <path>          安装到指定路径。
/install-options <...>   安装后以指定选项运行。
/uninstall <path>        从指定路径卸载。
```

> 提示：本分支也支持以 `-` 开头的开关（例如 `-fullscreen`）；若文件名以 `-` 开头，请用引号包裹或包含一个 `.` 以区分。

### 文件关联

在「选项 → 常规」中可勾选需要关联的图片格式，也可通过命令行 `/bmp /png ...` 静默安装关联。

---

## 配置

所有设置保存在 `voidImageViewer.ini`，常用项举例如下：

| 配置项 | 作用 | 默认值 |
| --- | --- | --- |
| `show_caption` | 显示系统标题栏 | `0`（隐藏） |
| `show_thickframe` | 显示系统粗边框 | `0`（隐藏） |
| `show_menu` | 显示菜单栏 | `0`（隐藏，用右键菜单） |
| `show_status` | 显示状态栏 | `0`（隐藏） |
| `show_controls` | 显示工具栏 | `0`（隐藏） |
| `fit_window_to_image` | 窗口自动贴合图片大小 | `1`（开启） |
| `transition_type` | 转场效果（0=无，1=淡入淡出） | `1` |
| `transition_duration` | 转场时长（毫秒，50–2000） | `300` |
| `hover_show_ui` | 鼠标悬停时显示界面 | `0` |
| `title_bar_format` | 标题栏格式（0=完整路径，1=仅文件名，2=无） | `1` |
| `slideshow_rate` | 幻灯片间隔（毫秒） | `5000` |
| `preload_next` | 预加载下一张 | `1` |
| `cache_last` | 缓存上一张 | `1` |
| `icm` | 启用色彩管理 | `1` |
| `orientation` | 支持 EXIF 方向 | `1` |

完整配置项见源码 [config.c](src/config.c)。

---

## 从源码构建

### 环境要求

- **Visual Studio 2026**（或兼容版本）。项目同时附带 `vs2005` 工程文件可供老版本使用。
- Windows SDK。
- 项目已内置 [libwebp](libwebp/) 源码，无需额外准备第三方依赖。

### 构建步骤

1. 用 Visual Studio 打开 `vs2026\voidImageViewer.sln`。
2. 选择配置（`Release`）与平台（`x64` 或 `Win32`）。
3. 生成解决方案，输出 `voidImageViewer.exe`。

> 渲染说明：当前使用 Windows GDI / GDI+（运行时动态加载 `gdiplus.dll`）进行图像渲染，兼容性好、依赖少。Direct3D / OpenGL 渲染器为计划中功能。

### 目录结构

```
voidImageViewer-master/
├── src/                # 主程序源码（纯 C / Win32 API）
│   ├── viv.c           # 主程序入口与核心逻辑
│   ├── config.c        # 配置读写
│   ├── render_*.c      # 渲染相关（gdi/software/d3d/opengl）
│   ├── webp.c          # WebP 解码封装
│   ├── localization*   # 多语言本地化（含简体中文）
│   └── ...
├── libwebp/            # 内置的 Google libwebp 源码
├── res/                # 资源文件（图标、菜单、清单）
├── nsis/               # NSIS 安装脚本
├── vs2005/             # VS2005 工程文件
├── vs2026/             # VS2026 工程文件
├── release/            # 预编译的 x86/x64 exe
├── Changes.txt         # 更新日志
├── LICENSE             # 许可证
└── README.md
```

---

## 已知问题与限制

以下为当前版本存在的已知问题或尚未实现的功能（整理自源码 TODO 与变更记录）：

- **无 SVG / AVIF / APNG 支持**：SVG、AVIF、APNG 尚在计划中，暂不支持。
- **GDI/GDI+ 2GB 限制**：受 GDI+ 限制，单张图像宽×高×4 受 2GB 内存约束，超大图存在上限。
- **旋转仅在内存中**：旋转操作不会写回原文件，仅影响当前显示。
- **剪贴板粘贴有限**：暂不支持从剪贴板直接粘贴图像显示（计划中）。
- **Direct3D / OpenGL 渲染器未实现**：目前仅 GDI/GDI+ 渲染，硬件加速渲染为计划功能。
- **暗色模式未支持**：Windows 暗色主题需自绘全部控件，暂未实现。
- **播放列表/相册文件**：暂不支持 m3u/efu 等播放列表文件格式。
- **多显示器感知**：未在鼠标所在显示器打开主窗口。
- **ARM/ARM64 安装包**：暂未提供。
- 部分老版本 Windows（如 Win9x）上删除操作可能存在崩溃风险。

如发现新问题，欢迎在 GitHub Issues 中反馈。

---

## 致谢

- **voidtools / David Carpenter** — 原版 [voidImageViewer](https://github.com/voidtools/voidImageViewer) 作者，极致简洁设计哲学的缔造者。
- **Google** — [libwebp](https://github.com/webmproject/libwebp) WebP 编解码库。
- 所有提交反馈与建议的用户。

---

## 许可证

本项目采用双许可证：

- **voidImageViewer**：[MIT License](LICENSE)，Copyright © 2025 voidtools / David Carpenter。
- **libwebp**：BSD 3-Clause License，Copyright © 2010 Google Inc.

本分支的汉化与增强改动同样以 MIT 协议开源，Copyright © 2026 hesphoros。

---

# void Image Viewer (Original)

A lightweight image viewer for Windows with animated GIF/WEBP support.
Opens and displays BMP, GIF, ICO, PNG, JPG, TIF and WEBP images as fast as possible.
Animate GIF/WEBP files as accurately as possible.

[Download](#下载)<br/>
[See also](#see-also)<br/>
<br/><br/><br/>

void Image Viewer main window:

![Void Image Viewer Image View](https://www.voidtools.com/voidImageViewer.Image.View10.gif)
<br/><br/><br/>

void Image Viewer General Options:

![Void Image Viewer Options General](https://www.voidtools.com/voidImageViewer.Options.General10.png)
<br/><br/><br/>

void Image Viewer View Options:

![Void Image Viewer Options View](https://www.voidtools.com/voidImageViewer.Options.View10.png)
<br/><br/><br/>

void Image Viewer Controls Options:

![Void Image Viewer Image Controls](https://www.voidtools.com/voidImageViewer.Options.Controls10.png)
<br/><br/><br/>

## See also

https://www.voidtools.com/forum/viewtopic.php?t=5623
