# voidImageViewer-i18n 3.7 开发者变更说明

本文件面向开发者，概括 3.7 相对 3.6 的代码结构、数据流、关键约束与验证结果。完整规格仍以 `01/02/03` 文档为准。

## 1. 代码落点

| 模块 | 文件 | 说明 |
|---|---|---|
| 最近打开 / 收藏夹 | `src/config.c/.h`、`src/viv.c` | 路径列表存储 + 动态菜单 + 管理对话框 |
| 播放列表筛选 | `src/viv.c` | 筛选谓词、导航候选、浮动筛选条 |
| 图片信息面板 | `src/viv.c`、`src/os.c/.h` | 对话框/ListView + 属性系统/GDI+ 元数据 |
| 资源 | `res/resource.h`、`res/voidImageViewer.rc` | 3 个新对话框、控件与版本资源 |
| 多语言 | `src/localization.h` + 10 张语言表 | 追加 71 条字符串，保持位置数组对齐 |
| 测试 | `tests/test_config_paths.c`、`tests/test_filter_logic.c` | 真实配置逻辑 + 筛选模型测试 |

## 2. 最近打开 / 收藏夹

- 数据：`recent_count` + `recent_0..19`，`favorite_count` + `favorite_0..99`。
- 去重：`StrCmpIW`，大小写不敏感；重复项移到最前。
- 上限：最近 20，收藏 100；超出淘汰最旧。
- 保存：最近退出时保存；收藏增删立即保存。
- 菜单：
  - `_VIV_MENU_FILE_RECENT`、`_VIV_MENU_FILE_FAVORITES` 两个弹出子菜单。
  - 动态 ID 区间 `20000..20019`、`21000..21099`。
  - 每次显示前重建；文件名 `&` 转义。
- 状态：当前图片路径统一由 `_viv_get_current_image_path()` 获取（current 优先、frame 兜底）。
- 刷新入口：图片加载、右键弹出、主菜单初始化、语言切换、空图/加载失败、收藏增删/管理。

## 3. 播放列表筛选

- 单一谓词 `_viv_filter_match(fd)`，不维护过滤数组。
- 文件名模式匹配 `cFileName` 的文件名部分；输入含 `\ / :` 时匹配完整路径。
- `_viv_next()`、`_viv_home()` 的所有分支（播放列表、目录扫描、洗牌）都跳过不匹配项。
- `_viv_preload_next()` 复用 `_viv_next(..., is_preload=1)`，自动继承筛选。
- 筛选激活且 0 匹配时，禁止 `_viv_home()` 调用 `_viv_blank()`。
- 手动打开/拖放/命令行加载时清空筛选。
- 筛选条：`IDD_FILTER`，`WS_EX_TOOLWINDOW`，主窗口移动/缩放时重新定位。

## 4. 图片信息面板

- UI：`IDD_IMAGE_INFO`，无模态 `CreateDialog` + `SysListView32` 两列，`WS_EX_TOOLWINDOW`。
- `os_get_image_metadata()`：
  1. `SHGetPropertyStoreFromIDList` + `IPropertyStore::GetValue`。
  2. 缺少任一核心字段时，GDI+ `GdipLoadImageFromFile` + `GdipGetPropertyItemSize/Item` 回退。
  3. 无数据时 UI 显示“无 EXIF 数据”。
- `os_get_image_pixel_info()`：像素格式、DPI、Alpha。
- 安全性：
  - `PROPVARIANT` 按类型读取，用完 `PropVariantClear`。
  - `__try/__except` 包裹属性处理器。
  - NaN、负数、超大值、畸形长度钳制。
  - 单次属性最大 1MB。
- 几何：`info_x/info_y/info_wide/info_high`，恢复时钳制到工作区。
- RTL：`_viv_apply_rtl()` 按当前语言设置/清除 `WS_EX_LAYOUTRTL`。

## 5. 多语言与资源约束

- 新字符串只能追加到 `LOCALIZATION_ID_*` 末尾。
- 必须同步追加到全部 10 张语言表；当前 334 条 = 334 条。
- 新增控件 ID：1070-1080；新增对话框：130-132。
- 版本：`version.h` 3.7.0，`.rc` 3.7.0.0，`nsis/version.nsh` 3.7 / 3.7.0.0。

## 6. 验证

- x64 / x86，Debug / Release 全部编译通过。
- `test_config_paths`：最近/收藏上限、去重、置顶、UTF-8 往返、特殊字符路径。
- `test_filter_logic`：大小写、文件名/路径模式、洗牌扫描、0 匹配保护。
- 语言表数量核对：10 张表均为 334 条。
- 未执行 GUI 自动化点击测试；界面部分需人工验收。
