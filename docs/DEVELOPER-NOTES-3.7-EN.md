# voidImageViewer-i18n 3.7 Developer Notes

This document summarizes the 3.7 code structure, data flow, key constraints and verification results relative to 3.6. The full specification still lives in the Chinese `01/02/03` documents.

## 1. Where the code lives

| Module | Files | Notes |
|---|---|---|
| Recent Files / Favorites | `src/config.c/.h`, `src/viv.c` | path-list storage + dynamic menus + manager dialog |
| Playlist filtering | `src/viv.c` | match predicate, navigation candidates, floating filter bar |
| Image Information | `src/viv.c`, `src/os.c/.h` | dialog/ListView + Property System/GDI+ metadata |
| Resources | `res/resource.h`, `res/voidImageViewer.rc` | three dialogs, controls and version resource |
| Localization | `src/localization.h` + 10 tables | 71 appended strings, positional alignment preserved |
| Tests | `tests/test_config_paths.c`, `tests/test_filter_logic.c` | real config logic + filter model tests |

## 2. Recent Files / Favorites

- Data: `recent_count` + `recent_0..19`, `favorite_count` + `favorite_0..99`.
- De-duplication: `StrCmpIW`, case-insensitive; a repeated path moves to the front.
- Limits: 20 recent, 100 favorites; oldest entries are evicted.
- Save policy: recent list on exit; favorite changes immediately.
- Menus:
  - `_VIV_MENU_FILE_RECENT` and `_VIV_MENU_FILE_FAVORITES` popups.
  - Dynamic ID ranges `20000..20019` and `21000..21099`.
  - Rebuilt before every display; `&` in file names is escaped.
- Current path: all consumers use `_viv_get_current_image_path()` (current first, frame fallback).
- Refresh points: image load, context-menu popup, main-menu init, language switch, blank/load failure, favorite add/remove/manager.

## 3. Playlist filtering

- One predicate `_viv_filter_match(fd)`; no separate filtered array.
- File-name mode matches the file-name part of `cFileName`; a query containing `\ / :` matches the full path.
- `_viv_next()` and `_viv_home()` skip non-matching entries in every branch (playlist, directory scan, shuffle).
- `_viv_preload_next()` reuses `_viv_next(..., is_preload=1)` and inherits the filter.
- If filtering is active with zero matches, `_viv_home()` must not call `_viv_blank()`.
- Manual open/drop/command-line load clears the filter.
- Filter bar: `IDD_FILTER`, `WS_EX_TOOLWINDOW`, repositioned when the main window moves/resizes.

## 4. Image Information

- UI: `IDD_IMAGE_INFO`, modeless `CreateDialog` + two-column `SysListView32`, `WS_EX_TOOLWINDOW`.
- `os_get_image_metadata()`:
  1. `SHGetPropertyStoreFromIDList` + `IPropertyStore::GetValue`.
  2. GDI+ `GdipLoadImageFromFile` + `GdipGetPropertyItemSize/Item` fallback when any core field is missing.
  3. UI shows “No readable EXIF data” when nothing is available.
- `os_get_image_pixel_info()`: pixel format, DPI, alpha flag.
- Safety:
  - `PROPVARIANT` is read by type and cleared with `PropVariantClear`.
  - Property handlers are wrapped in `__try/__except`.
  - NaN, negative, oversized and malformed values are clamped.
  - A single property is capped at 1 MB.
- Geometry: `info_x/info_y/info_wide/info_high`, clamped to the work area on restore.
- RTL: `_viv_apply_rtl()` sets or clears `WS_EX_LAYOUTRTL` according to the current language.

## 5. Localization and resource constraints

- New strings may only be appended to the `LOCALIZATION_ID_*` enum.
- All ten positional language tables must be appended in the same order; currently 334 entries each.
- New control IDs: 1070-1080; new dialogs: 130-132.
- Version: `version.h` 3.7.0, `.rc` 3.7.0.0, `nsis/version.nsh` 3.7 / 3.7.0.0.

## 6. Verification

- x64 / x86, Debug / Release all compile.
- `test_config_paths`: limits, de-duplication, move-to-front, UTF-8 round-trip, special-character paths.
- `test_filter_logic`: case-insensitivity, file-name/path modes, shuffle scan, zero-match protection.
- Localization audit: all ten tables have 334 entries.
- No automated GUI click test was run; the UI still needs manual acceptance.
