# void Image Viewer (Multilingual & Enhanced Fork)

English | [简体中文](README_CN.md)

> A lightweight, blazing-fast image viewer built for Windows, featuring seamless switching between 10 UI languages, 1:1 pixel-perfect zoom by default, and smooth animated GIF / WebP playback.
> This project is based on [voidtools/voidImageViewer](https://github.com/voidtools/voidImageViewer) with immersive-experience enhancements and multilingual support.
> **Current version: v3.2**

[Download](#download) | [Key Changes](#key-changes-compared-to-the-original) | [Features](#features) | [Usage](#usage) | [Building from Source](#building-from-source) | [License](#license-and-acknowledgements)

---

## About This Fork

First and foremost, our deepest respect goes to the original author **voidtools / David Carpenter**. `voidImageViewer` inherits the same design philosophy as [Everything](https://www.voidtools.com/) — ultra-lightweight, millisecond-level startup, and a low memory footprint.

This fork builds on that foundation with comprehensive enhancements: **10 UI languages**, **1:1 actual-size viewing by default with persistent settings**, plus immersive experience improvements such as cross-fade transitions.

### Key Changes Compared to the Original

| Area | Description |
| --- | --- |
| **Multilingual support (i18n)** | 10 built-in languages (Simplified Chinese, English, Japanese, Korean, French, German, Spanish, Portuguese, Italian, Arabic), automatic system-language detection, instant switching from the menu (no restart required), and automatic RTL layout for Arabic. |
| **Default 1:1 actual-size zoom** | Overrides the original fit-to-window zoom logic: images open at **1:1 (100%) original pixel size** by default, and the preference is persisted in `voidImageViewer.ini`. |
| **Slideshow cross-fade transition** | Adds a smooth fade-in/fade-out transition between slideshow slides. Enable it under "View → Transition Effect" with a customizable duration (50–2000 ms). |
| **Borderless immersive viewing** | Hides the title bar, menu bar, status bar and thick window borders by default; everything is controlled via the right-click menu and keyboard shortcuts to maximize the viewing area. |
| **Window fit & title options** | The window can auto-fit to the image size to eliminate white margins; the title bar can show the full path, the file name only, or nothing at all. |
| **Documentation** | Complete technical documentation, configuration guide and build instructions in both English and Chinese. |
| **Stability hardening (v3.2)** | Fixed a crash when deleting images during shuffle playback (use-after-free) and undefined behavior in animation pause / status-bar pixel values; consolidated duplicated parsing code in the Everything integration while keeping all safety checks; removed build artifacts and dead code from the repository. |

---

## Features

### Multilingual & Localization

- **Seamless switching between 10 languages**:
  - Simplified Chinese (`Simplified Chinese`)
  - English (`English`)
  - Japanese (`Japanese`)
  - Korean (`Korean`)
  - French (`French`)
  - German (`German`)
  - Spanish (`Spanish`)
  - Portuguese (`Portuguese`)
  - Italian (`Italian`)
  - Arabic (`Arabic` — supports RTL right-to-left mirrored layout)
- **Smart language detection**: automatically detects the Windows system language on first launch and falls back to English if it is not in the supported list.
- **Dynamic redraw**: switching languages takes effect instantly without a restart — the menu bar, context menu and dialogs all update on the fly.

### Image Formats & Decoding

- **Currently supported formats**:
  - **Common formats**: JPEG/JPG, PNG, BMP, TIFF/TIF, ICO (GDI+ / native Win32).
  - **WebP**: static WebP and multi-frame animated WebP (with a bundled lightweight `libwebp` decoder).
  - **Animated GIF**: frame-by-frame playback (native GDI+).
  - **HEIC/HEIF**: bundled `libheif` + `libde265` open-source decoders (MIT licensed), works out of the box — **no need** to install the system "HEIF Image Extensions" component; supports HEVC photos shot on iPhone and other devices, with automatic EXIF orientation rotation.
- **Extra-large image rendering**: high-resolution image rendering and panning, with a built-in safe-arithmetic library that guards against memory-size multiplication overflow.
- **Note**: decoders for formats such as AVIF, APNG, TGA, WMF/EMF and CUR/ANI are not implemented yet and have been removed from the file picker and the Everything search filters accordingly, avoiding "listed but cannot open" situations.

#### Supported Image Formats at a Glance

| Category | Extensions | Decoder / Implementation | Rendering Notes |
| :--- | :--- | :--- | :--- |
| **Common standard formats** | `.jpg`, `.jpeg`, `.png`, `.bmp`, `.tif`, `.tiff`, `.ico` | GDI+ / native Win32 | Exif auto-rotation, alpha transparency, crisp pixel rendering |
| **Animated GIF** | `.gif` | GDI+ frame decoding | Frame-by-frame animated GIF playback with playback controls |
| **WebP** | `.webp` | Bundled open-source `libwebp` decoder | Static WebP and smooth multi-frame animated WebP playback |
| **HEIC/HEIF** | `.heic`, `.heif` | Bundled `libheif` + `libde265` decoders (uses the system WIC component first when available) | Opens iPhone HEVC photos without the system HEIF extension |

### Viewing & Zooming

- **Multiple zoom modes**: 1:1 actual size (default) / Best fit / Fill window / Allow shrink / Maintain aspect ratio.
- **Pan & Scan**: fine-tuning in eight directions, centering, and proportional canvas/window adjustment.
- **Smart drag panning (v3.1)**: when the image is zoomed in beyond the window, hold the left mouse button and drag to pan around; when the image is fully visible, dragging a normal window still moves the window, and a maximized window will not be accidentally restored. Fullscreen and caption-visible modes behave as before.
- **High-performance mipmaps**: pre-generates multi-level downscaled images for zoomed-out display, eliminating pixel-aliasing artifacts and improving rendering performance.
- **Smooth zooming**: fine adjustment with the mouse wheel plus smooth zoom in/out via hotkeys.

### Animation & Slideshow

- **Animation controls**: play/pause, single-frame stepping, jump to first/last frame, and playback speed adjustment (faster/slower/reset).
- **Slideshow**: customizable interval from 250 ms to 60 s, or automatic playback following the animation's intrinsic frame rate.
- **Cross-fade transition**: fade-in/fade-out transition animation with a customizable duration (50 ms–2000 ms).
- **Sleep prevention**: automatically blocks the screensaver and system sleep while a slideshow or animation is playing.

### Navigation & Everything Integration

- **Smart preloading**: "preload next image" and "cache previous image" for lag-free image switching.
- **Flexible sorting**: by file name, file size, modification time, creation time, or full path, in ascending/descending order, with **Natural Sort** support.
- **Everything integration**: directly use local global search results from [Everything](https://www.voidtools.com/) as the image playlist.

### File & Editing Operations

- **File management**: open single files/folders, drag-and-drop loading, quick cut/copy/paste, and move/copy to a specified directory.
- **Clipboard & image handling**: copy the image to the clipboard in one click, copy the file path, automatic rotation by EXIF orientation (`System.Photo.Orientation`), and lossless rotation.
- **Wallpaper & printing**: set the image as the desktop wallpaper and invoke the system print dialog.

### Interface & Hotkey Customization

- **Key mapping**: every keyboard shortcut can be added, modified and removed.
- **Mouse hotkeys**: left button, right button, wheel, Ctrl+wheel, side buttons (XButton) and more can be freely assigned (e.g. drag-pan, wheel zoom, image switching).
- **Portable configuration**: settings are written to `voidImageViewer.ini`, saved either next to the executable or in `%APPDATA%`, with multi-instance support.

---

## Download

- **Release builds**: visit the GitHub [Releases](../../releases) page to download the latest build.
- **Official original resources**:
  - Voidtools forum thread: [https://www.voidtools.com/forum/viewtopic.php?t=5623](https://www.voidtools.com/forum/viewtopic.php?t=5623)
  - Voidtools GitHub repository: [https://github.com/voidtools/voidImageViewer](https://github.com/voidtools/voidImageViewer)

**v3.2 release files**: portable ZIP archives for 32-bit (`x86`) and 64-bit (`x64`) — extract and run; standard NSIS installers (Chinese/English) are also provided.

| Type | File |
| --- | --- |
| Portable x64 | `voidImageViewer-3.2.x64.zip` |
| Portable x86 | `voidImageViewer-3.2.x86.zip` |
| Installer x64 Chinese | `voidImageViewer-3.2.x64.zh-CN-Setup.exe` |
| Installer x64 English | `voidImageViewer-3.2.x64.en-US-Setup.exe` |
| Installer x86 Chinese | `voidImageViewer-3.2.x86.zh-CN-Setup.exe` |
| Installer x86 English | `voidImageViewer-3.2.x86.en-US-Setup.exe` |

---

## Usage

### Quick Start

1. Double-click `voidImageViewer.exe` to launch, or drag image files directly into the program window.
2. **Right-click** to bring up the main menu (borderless immersive mode is enabled by default).
3. Scroll the mouse wheel or press `↑` / `↓` to switch to the previous/next image.
4. Press `F` or use the right-click menu to enter fullscreen mode.

### Switching the UI Language

Right-click inside the window and choose **View → Language**, then click the language you want — the interface switches instantly.

### Command-line Options

Run `voidImageViewer.exe /?` in a command prompt to see the help:

```text
Usage:
voidImageViewer.exe [/switches] [filename...]

Common switches:
/slideshow      Start playing a slideshow right after launch.
/fullscreen     Start in fullscreen mode.
/maximized      Start with the window maximized.
/window         Start in normal window mode.
/ontop          Keep the window always on top.
/minimal        Start in borderless mode.
/compact        Start with a compact border.
/x <x> /y <y> /width <w> /height <h>   Custom initial window position and size.
/rate <ms>      Slideshow interval in milliseconds.
/name           Sort by file name.
/size           Sort by file size.
/dm             Sort by modification time.
/shuffle        Shuffle the playlist.
/appdata        Force the configuration into the AppData directory.
/noappdata      Force the configuration next to the EXE (portable mode).
```

*Note: this fork also fully accepts switches with a `-` prefix (e.g. `-fullscreen`).*

---

## Configuration

All settings are stored in the `voidImageViewer.ini` file. Common key options:

| Key | Description | Default |
| --- | --- | --- |
| `language` | UI language (`-1` = auto detect, `0` = English, `1` = Chinese...) | `-1` |
| `auto_zoom` | Enable automatic zoom settings | `1` |
| `auto_zoom_type` | Auto zoom type (`0` = fit window, `1` = 100% / 1:1 actual size) | `1` |
| `fit_window_to_image` | Auto-fit the window to the image size | `1` |
| `show_caption` | Show the window title bar | `0` (hidden) |
| `show_menu` | Show the main menu bar | `0` (hidden) |
| `show_status` | Show the bottom status bar | `0` (hidden) |
| `transition_type` | Slideshow transition effect (`0` = none, `1` = cross-fade) | `1` |
| `transition_duration` | Cross-fade transition duration in ms (50–2000) | `300` |
| `title_bar_format` | Title bar format (`0` = full path, `1` = file name only, `2` = none) | `1` |
| `preload_next` | Preload the next image | `1` |
| `cache_last` | Cache the previous image | `1` |

---

## Building from Source

This project is written in standard C and depends on the Win32 API.

### Requirements

- **Compiler**: Microsoft Visual Studio 2026 or newer (with the "Desktop development with C++" workload; the project toolset is `v145`)
- **Build tool**: MSBuild
- **Supported systems**: Windows 7 / 8 / 10 / 11

### Build Steps

1. Clone the repository:
   ```bash
   git clone https://github.com/your-username/voidImageViewer.git
   cd voidImageViewer
   ```
2. Open `vs2026/voidImageViewer.sln` in Visual Studio.
3. Select the target platform (`x64` or `x86`) and the configuration (`Release`).
4. Click **Build → Build Solution**. The compiled executable is placed under `vs2026/x64/Release/` (x64) or `vs2026/Release/` (x86).

You can also run the one-click build script from the command line (requires Visual Studio 2026 with MSBuild available in your environment):

```cmd
build_release_both.bat
```

This script builds the Release version for both x64 and Win32.

---

## License and Acknowledgements

- **License**: this project is released under the [MIT License](LICENSE).
- **Original author**: [voidtools / David Carpenter](https://www.voidtools.com/).
- **Third-party decoder library**: bundles [libwebp](https://chromium.googlesource.com/webm/libwebp) to provide full WebP decoding support.
