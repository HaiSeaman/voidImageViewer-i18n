# RELEASE NOTES — voidImageViewer-i18n 3.7

Release date: 2026-11-18  
Previous version: 3.6 (2026-10-14)

## One-line summary

3.7 keeps the viewer lightweight, single-file and dependency-free while adding three practical modules — **Recent Files / Favorites**, **playlist filtering by name**, and an **Image Information panel (EXIF/GPS)** — plus a stability pass over menus, navigation, configuration and metadata reading.

---

## 1. Recent Files / Favorites (new)

- Two new submenus under File: **Recent Files** and **Favorites**; both are also available from the right-click menu.
- Recent Files automatically records successfully displayed images, up to **20** entries, newest first, with case-insensitive de-duplication.
- Favorites lets you add/remove the current image, up to **100** entries, with a **Manage Favorites** dialog (open, remove, clear).
- Storage stays in the single `voidImageViewer.ini`:
  - `recent_count` / `recent_0..19`
  - `favorite_count` / `favorite_0..99`
- Paths are de-duplicated case-insensitively; Chinese characters, spaces, `&` and `=` in paths are preserved correctly.
- Recent entries are saved on exit; favorite changes are saved immediately to survive a crash.
- Missing files: recent entries show “File not found” and are removed; favorites are kept so external drives can be reconnected.
- `&` in menu text is escaped so file names are not interpreted as menu mnemonics.

## 2. Playlist Filtering by Name (new)

- Press `Alt+F` to open a floating filter bar at the top of the window.
- Live filtering by file-name substring (case-insensitive); if the query contains `\`, `/` or `:`, it matches the full path.
- The bar shows the match count; `Enter` jumps to the next match, `Esc` clears and closes.
- Filtering only affects navigation candidates — it never deletes or reorders the playlist:
  - previous / next
  - first / last
  - shuffle
  - background preloading
- **Zero matches never clear the playlist**; the current image stays visible.
- Opening a file/folder or dropping files clears the filter automatically.
- Filtering is unavailable in Everything random mode and shows a hint.

## 3. Image Information Panel (new)

- Press `Ctrl+I` to open a **modeless tool window**; you can keep browsing while it updates automatically.
- Two-column ListView (Property / Value) with full-row selection, scrolling and copying.
- Sections:
  - **File**: name, full path, size, created time, modified time
  - **Image**: format, dimensions, bit depth, alpha, DPI, frame count, current frame, frame delay, duration, estimated decode memory
  - **EXIF**: camera make/model, lens, software, date taken, exposure time, aperture, ISO, focal length, 35 mm equivalent, exposure bias, flash, metering, white balance, exposure program, description, artist, copyright, EXIF version, color space, orientation
  - **GPS**: latitude, longitude, altitude, direction
- EXIF strategy (option B): Windows Property System first, GDI+ property fallback when core fields are missing; if nothing is readable, the panel says “No readable EXIF data”.
- “Copy All” / `Ctrl+C` copies the information as text.
- Remembers window position and size; supports RTL layout and high DPI.
- Malformed EXIF values (NaN, infinity, negative/oversized coordinates) are clamped to avoid undefined behaviour.

## 4. Fixes included in 3.7

- **“Add to Favorites” always greyed out**: image load only refreshed Recent Files, not Favorites, and the right-click menu did not force a refresh. The menu now refreshes on image load, right-click, language switch, blank image and load failure.
- **Wrong recent path during preload activation**: now prefers the current image path with the displayed frame as fallback.
- **Filter with zero matches cleared the playlist**: `_viv_home` called `_viv_blank()` with no candidates; guarded while filtering.
- **Dynamic menus not refreshed after a right-click command**: clear `_viv_in_popup_menu` before dispatching the command.
- **Buffer overrun risk in menu text / Copy All**: removed the fixed-1024 assumption of `string_cat`; both now use bounded appends.
- **RTL layout remained after switching from Arabic back to English**: information and filter windows now set/clear `WS_EX_LAYOUTRTL` consistently.
- **Image Information appeared in the taskbar**: added `WS_EX_TOOLWINDOW`.
- **Malformed EXIF/GPS numbers**: added NaN/negative/oversized/type checks before integer conversion.
- **Dead-code cleanup**: removed unused globals, a duplicate property struct, an empty status control and unused parameters; unified current-image path selection.

## 5. Compatibility & known limitations

- Still pure C + Win32, single-file exe, `/MT` static CRT, no new runtime dependencies.
- Windows 7 / 8 / 10 / 11, x86 and x64.
- HEIC/HEIF EXIF still depends on the system HEIF extension or codec; without it, only basic file/image information is shown.
- WebP EXIF also depends on the system codec.
- The Image Information panel reads metadata synchronously; network paths may briefly block the UI.
- Filter counts are computed on every keystroke; very large folders may feel slightly delayed.

## 6. Release files

- Portable x64: `voidImageViewer-3.7.x64.zip`
- Portable x86: `voidImageViewer-3.7.x86.zip`
- Installer x64 Chinese: `voidImageViewer-3.7.x64.zh-CN-Setup.exe`
- Installer x64 English: `voidImageViewer-3.7.x64.en-US-Setup.exe`
- Installer x86 Chinese: `voidImageViewer-3.7.x86.zh-CN-Setup.exe`
- Installer x86 English: `voidImageViewer-3.7.x86.en-US-Setup.exe`

## 7. Upgrade notes

- You can replace the old exe directly; `voidImageViewer.ini` remains backward compatible. New `recent_*`, `favorite_*` and `info_*` keys are written automatically.
- Older versions ignore the new keys and will not corrupt the configuration.
- Back up `voidImageViewer.ini` before testing if you want a clean baseline.
