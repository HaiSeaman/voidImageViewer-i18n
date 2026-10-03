# RELEASE NOTES — voidImageViewer-i18n 3.5

发布日期：2026-10-03
上一版本：3.4（2026-09-16）

## 一句话版本

精简右键一级菜单（移除与【视图】子菜单重复的 4 个开关），修复 6 处稳定性隐患（失败字符串未正确收尾、重复的 1:1 勾选刷新、未初始化局部变量、未判空的画笔句柄、头文件重复声明），清理 15 个无用资源 ID 与仓库残留产物。

## 变更

- **右键一级菜单精简（本版核心改动）**：无边框模式下右键弹出的菜单，最上层不再重复【视图】里的 4 个开关——**允许缩小、保持纵横比、填充窗口、1:1**。原因是右键菜单本身已经**完整挂接了【视图】子菜单**，这 4 个功能在那里本来就有，顶部再列一份是纯粹的重复。本次只删除右键弹窗里的这 4 个重复入口，**命令、处理函数、快捷键（1:1 = Ctrl+Alt+0）与勾选状态刷新全部保持不变**；弹出菜单原有的分隔符去重逻辑会让精简后的版面自动收紧。
- **版本号升级至 3.5**：`src/version.h`、`res/voidImageViewer.rc` 的 VERSIONINFO、NSIS 的 `nsis/version.nsh` 三处同步，软件属性显示 `3.5.0.0`；`README.md` / `README_CN.md` 顶部版本号同步。

## 修复（6 处稳定性隐患）

- **失败路径未正确收尾**：`string_copy_utf8_string` 在复制失败时，把字符串结束符写到了 `buf[STRING_SIZE - 1]`（缓冲区最后一个字节）而不是 `buf[0]`，导致目标缓冲区前面全是垃圾数据、只有最后一字节被清零。现改为在索引 0 处收尾。
- **重复的 1:1 勾选刷新**：同一例程内对 `VIV_ID_VIEW_1TO1` 的 `CheckMenuItem` 勾选刷新写了两遍（重复调用），删除第二处冗余调用。
- **未初始化的局部变量**：关于对话框的 `LOGFONT` 现零初始化（`{0}`）；临时图像指针 `image` 显式初始化为 `0`。
- **未判空的画笔句柄**：绘制用到 `CreatePen` 时，现在会先判断返回值是否为 NULL，再选入设备上下文。
- **头文件重复声明**：`config.h` 里 `config_auto_zoom` 被声明了两次，删除重复的 `extern`。

## 仓库整理

- 删除 `res/resource.h` 中 15 个已无任何引用的资源 ID：`IDD_FORMVIEW`、`IDD_FORMVIEW1`、`IDD_FORMVIEW2`、`IDD_DIALOG1`、`IDB_BITMAP1`、`IDI_ICON2`、`IDC_COMBO3`、`IDC_CHECK1`、`IDC_BUTTON1`、`IDC_BUTTON2`、`IDC_BUTTON3`、`IDC_LIST1`、`IDC_LIST2`、`IDC_OLD_EDIT`、`IDC_EDIT1`。
- 删除仓库根目录残留的编译产物 `test_left_drag.obj`、`test_playlist_delete.obj`。

## 审计结论

- **视频能力复核**：本软件为纯图片查看器，**不含任何视频播放能力**。链接库仅 ComCtl32 / sh1wapi / windowscodecs / ole32 / heif / libde265 等，无 FFmpeg、DirectShow、Media Foundation、MCI 等视频相关库；代码无相关接口调用；可打开的文件类型仅图片格式。菜单里的"播放/暂停"实为**幻灯片自动翻张**与**动图（GIF / 动态 WebP）逐帧播放**。
- **代码洁净度**：资源 ID 与源码引用一一对应；菜单命令表与右键条目序列无悬空引用。

## 回归验证

- x64 Release 编译通过，`/W3` 0 警告，重新生成的 `voidImageViewer.exe` 属性报告 `FileVersion = 3.5.0.0`、`ProductVersion = 3.5.0.0`。
- 右键一级菜单：经代码核对，4 个重复入口已从右键条目数组中移除，4 个功能仍完整保留在【视图】子菜单内，命令 ID 与处理函数未改动。

## 升级说明

- 便携版：直接替换 `voidImageViewer.exe`（配置 ini 兼容，无新增/删除配置项）。
- 安装版：NSIS 安装包沿用旧配置升级安装。
- 语言 / 快捷键：本次未增删任何本地化字符串，也未改动快捷键，用户既有配置与习惯不受影响。

## GitHub Release 简介（可直接复制粘贴）

### English

**voidImageViewer-i18n v3.5 — A cleaner context menu, a more solid core**

This release is a "subtract and harden" pass: duplicated entries were removed from the right-click menu to keep the UI clean, six small defects that could lead to unexpected behaviour were fixed, and a batch of unused resources and stray build artifacts was cleaned out of the repository.

**What's new**
- **Slimmer context menu**: the right-click popup no longer repeats the four View toggles "Allow Shrinking / Keep Aspect Ratio / Fill Window / 1:1" as top-level entries. They already live in the "View" submenu (which the context menu appends in full), so the extra copies were pure duplication. The commands, their handlers and the Ctrl+Alt+0 shortcut for 1:1 are all fully preserved — just use them from "View".
- **Six stability fixes**: a failed string copy did not terminate the buffer correctly; the 1:1 check-mark state was refreshed twice; an uninitialized local `LOGFONT` in the About dialog; an uninitialized temporary image pointer; an unchecked `CreatePen` handle; and a duplicated declaration in a header.
- **Repository cleanup**: removed 15 unused resource IDs and leftover build artifacts — a cleaner project tree.

**Version info**
- Software version: 3.5 (file properties show 3.5.0.0)
- Supported systems: Windows 7 / 8 / 10 / 11 (x64 / x86)
- Config compatibility: fully compatible with 3.4 — just replace the executable

**Downloads**
- Portable: run `voidImageViewer.exe` directly, no installation required
- Installer: NSIS setup (Chinese / English)

### 简体中文

**voidImageViewer-i18n v3.5 — 右键菜单更清爽，底层更稳**

这个版本做了一次"减法 + 加固"：把右键菜单里重复的功能入口去掉，让界面更干净；顺手修掉了 6 处可能导致异常的小隐患，并清理了一批仓库里的无用资源与残留文件。

**本次更新**
- 精简右键一级菜单：移除与【视图】子菜单重复的「允许缩小 / 保持纵横比 / 填充窗口 / 1:1」4 个入口，功能与快捷键完全保留（在「视图」里操作即可），菜单更清爽。
- 修复 6 处稳定性隐患：字符串复制失败未正确收尾、1:1 勾选状态重复刷新、未初始化的局部变量、未判空的画笔句柄、头文件重复声明。
- 仓库整理：删除 15 个无用资源 ID 与残留编译产物，工程更干净。

**版本信息**
- 软件版本：3.5（属性显示 3.5.0.0）
- 支持系统：Windows 7 / 8 / 10 / 11（x64 / x86）
- 配置兼容：与 3.4 完全兼容，直接替换 exe 即可

**安装包**
- 便携版：解压即用，无需安装
- 安装版：NSIS 安装包（中 / 英双语）