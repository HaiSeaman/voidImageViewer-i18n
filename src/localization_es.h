//
// Copyright 2026 hesphoros
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//
// Español localization
// Save as UTF-8 with BOM (required for MSVC to parse non-ASCII correctly).

const utf8_t *_localization_string_array_es[LOCALIZATION_ID_COUNT] = 
{
	// Application name
	"Español", // LOCALIZATION_ID_LANGUAGE

	// Language names (for the language selection menu)
	"English (US)", // LOCALIZATION_ID_LANGUAGE_ENGLISH
	"简体中文", // LOCALIZATION_ID_LANGUAGE_CHINESE_SIMPLIFIED
	"日本語", // LOCALIZATION_ID_LANGUAGE_JAPANESE
	"한국어", // LOCALIZATION_ID_LANGUAGE_KOREAN
	"Français", // LOCALIZATION_ID_LANGUAGE_FRENCH
	"Deutsch", // LOCALIZATION_ID_LANGUAGE_GERMAN
	"Español", // LOCALIZATION_ID_LANGUAGE_SPANISH
	"Português", // LOCALIZATION_ID_LANGUAGE_PORTUGUESE
	"Italiano", // LOCALIZATION_ID_LANGUAGE_ITALIAN
	"العربية", // LOCALIZATION_ID_LANGUAGE_ARABIC
	
	// Application name
	"void Image Viewer", // LOCALIZATION_ID_APP_NAME

	// File menu
	"&Archivo", // LOCALIZATION_ID_FILE,
	"&Abrir archivo...", // LOCALIZATION_ID_OPEN_FILE,
	"Abrir &carpeta...", // LOCALIZATION_ID_OPEN_FOLDER,
	"Abrir &búsqueda de Everything...", // LOCALIZATION_ID_OPEN_EVERYTHING_SEARCH,
	"&Agregar archivo...", // LOCALIZATION_ID_ADD_FILE,
	"Agregar carpeta...", // LOCALIZATION_ID_ADD_FOLDER,
	"Agregar búsqueda de Everything...", // LOCALIZATION_ID_ADD_EVERYTHING_SEARCH,
	"Abrir &ubicación del archivo...", // LOCALIZATION_ID_OPEN_FILE_LOCATION,
	"&Editar...", // LOCALIZATION_ID_EDIT,
	"&Vista previa...", // LOCALIZATION_ID_PREVIEW,
	"&Imprimir...", // LOCALIZATION_ID_PRINT,
	"Establecer como fondo de &escritorio", // LOCALIZATION_ID_SET_DESKTOP_WALLPAPER,
	"&Cerrar", // LOCALIZATION_ID_CLOSE,
	"&Eliminar", // LOCALIZATION_ID_DELETE,
	"Eliminar (Papelera)", // LOCALIZATION_ID_DELETE_RECYCLE,
	"Eliminar (Definitivamente)", // LOCALIZATION_ID_DELETE_PERMANENTLY,
	"&Renombrar", // LOCALIZATION_ID_RENAME,
	"&Propiedades", // LOCALIZATION_ID_PROPERTIES,
	"&Salir", // LOCALIZATION_ID_EXIT,
	
	// Edit menu
	"&Editar", // LOCALIZATION_ID_EDIT_MENU,
	"Cor&tar", // LOCALIZATION_ID_CUT,
	"&Copiar", // LOCALIZATION_ID_COPY,
	"Copiar nombre de archivo", // LOCALIZATION_ID_COPY_FILENAME,
	"Copiar &imagen", // LOCALIZATION_ID_COPY_IMAGE,
	"&Pegar", // LOCALIZATION_ID_PASTE,
	"Girar en sentido &horario", // LOCALIZATION_ID_ROTATE_CLOCKWISE,
	"Girar en sentido &antihorario", // LOCALIZATION_ID_ROTATE_COUNTERCLOCKWISE,
	"Copiar a &carpeta...", // LOCALIZATION_ID_COPY_TO,
	"&Mover a carpeta...", // LOCALIZATION_ID_MOVE_TO,
	
	// View menu
	"&Ver", // LOCALIZATION_ID_VIEW,
	"Leyenda", // LOCALIZATION_ID_CAPTION,
	"Marco", // LOCALIZATION_ID_FRAME,
	"&Menú", // LOCALIZATION_ID_MENU,
	"&Barra de estado", // LOCALIZATION_ID_STATUS_BAR,
	"&Controles", // LOCALIZATION_ID_CONTROLS,
	"&Preajuste", // LOCALIZATION_ID_PRESET,
	"&Mínimo", // LOCALIZATION_ID_MINIMAL,
	"&Compacto", // LOCALIZATION_ID_COMPACT,
	"&Normal", // LOCALIZATION_ID_NORMAL,
	"&Pantalla completa", // LOCALIZATION_ID_FULLSCREEN,
	"&Diapositivas", // LOCALIZATION_ID_SLIDESHOW,
	"&Tamaño de ventana", // LOCALIZATION_ID_VIEW_WINDOW_SIZE,
	"50%", // LOCALIZATION_ID_VIEW_WINDOW_SIZE_50_PERCENT,
	"100%", // LOCALIZATION_ID_VIEW_WINDOW_SIZE_100_PERCENT,
	"200%", // LOCALIZATION_ID_VIEW_WINDOW_SIZE_200_PERCENT,
	"&Ajuste automático", // LOCALIZATION_ID_VIEW_WINDOW_SIZE_AUTO_FIT,
	"&Actualizar", // LOCALIZATION_ID_REFRESH,
	"&Permitir reducción", // LOCALIZATION_ID_ALLOW_SHRINKING,
	"&Mantener proporción", // LOCALIZATION_ID_KEEP_ASPECT_RATIO,
	"&Rellenar ventana", // LOCALIZATION_ID_FILL_WINDOW,
	"1:1", // LOCALIZATION_ID_ONE_TO_ONE,
	"&Mejor ajuste", // LOCALIZATION_ID_BEST_FIT,
	"&Panorámica && escaneo", // LOCALIZATION_ID_PAN_SCAN,
	"&Aumentar tamaño", // LOCALIZATION_ID_INCREASE_SIZE,
	"&Disminuir tamaño", // LOCALIZATION_ID_DECREASE_SIZE,
	"A&umentar ancho", // LOCALIZATION_ID_INCREASE_WIDTH,
	"D&isminuir ancho", // LOCALIZATION_ID_DECREASE_WIDTH,
	"Aum&entar alto", // LOCALIZATION_ID_INCREASE_HEIGHT,
	"Disminuir &alto", // LOCALIZATION_ID_DECREASE_HEIGHT,
	"&Zoom", // LOCALIZATION_ID_ZOOM,
	"Zoom &adentro", // LOCALIZATION_ID_ZOOM_IN,
	"Zoom &afuera", // LOCALIZATION_ID_ZOOM_OUT,
	"&Restablecer", // LOCALIZATION_ID_RESET,
	"Mover &arriba", // LOCALIZATION_ID_MOVE_UP,
	"Mover &abajo", // LOCALIZATION_ID_MOVE_DOWN,
	"Mover a la &izquierda", // LOCALIZATION_ID_MOVE_LEFT,
	"Mover a la &derecha", // LOCALIZATION_ID_MOVE_RIGHT,
	"Mover arriba a la izquierda", // LOCALIZATION_ID_MOVE_UP_LEFT,
	"Mover arriba a la derecha", // LOCALIZATION_ID_MOVE_UP_RIGHT,
	"Mover abajo a la izquierda", // LOCALIZATION_ID_MOVE_DOWN_LEFT,
	"Mover abajo a la derecha", // LOCALIZATION_ID_MOVE_DOWN_RIGHT,
	"Mover al &centro", // LOCALIZATION_ID_MOVE_CENTER,
	"Re&stablecer", // LOCALIZATION_ID_PANSCAN_RESET,
	"Siempre al &frente", // LOCALIZATION_ID_ON_TOP,
	"&Siempre", // LOCALIZATION_ID_ALWAYS,
	"&Mientras se reproduce diapositivas o animación", // LOCALIZATION_ID_WHILE_PLAYING_OR_ANIMATING,
	"&Nunca", // LOCALIZATION_ID_NEVER,
	"&Opciones...", // LOCALIZATION_ID_OPTIONS,
	"&Transición", // LOCALIZATION_ID_TRANSITION,
	"&Ninguna", // LOCALIZATION_ID_TRANSITION_NONE,
	"&Fundido", // LOCALIZATION_ID_TRANSITION_FADE,
	"Duración...", // LOCALIZATION_ID_TRANSITION_DURATION,
	
	// Slideshow menu
	"&Diapositivas", // LOCALIZATION_ID_SLIDESHOW_MENU,
	"&Reproducir/Pausar", // LOCALIZATION_ID_PLAY_PAUSE,
	"&Velocidad", // LOCALIZATION_ID_RATE,
	"&Disminuir velocidad", // LOCALIZATION_ID_DECREASE_RATE,
	"&Aumentar velocidad", // LOCALIZATION_ID_INCREASE_RATE,
	"250 milisegundos", // LOCALIZATION_ID_RATE_250_MILLISECONDS,
	"500 milisegundos", // LOCALIZATION_ID_RATE_500_MILLISECONDS,
	"&1 segundo", // LOCALIZATION_ID_RATE_1_SECOND,
	"&2 segundos", // LOCALIZATION_ID_RATE_2_SECONDS,
	"&3 segundos", // LOCALIZATION_ID_RATE_3_SECONDS,
	"&4 segundos", // LOCALIZATION_ID_RATE_4_SECONDS,
	"&5 segundos", // LOCALIZATION_ID_RATE_5_SECONDS,
	"&6 segundos", // LOCALIZATION_ID_RATE_6_SECONDS,
	"&7 segundos", // LOCALIZATION_ID_RATE_7_SECONDS,
	"&8 segundos", // LOCALIZATION_ID_RATE_8_SECONDS,
	"&9 segundos", // LOCALIZATION_ID_RATE_9_SECONDS,
	"1&0 segundos", // LOCALIZATION_ID_RATE_10_SECONDS,
	"20 segundos", // LOCALIZATION_ID_RATE_20_SECONDS,
	"30 segundos", // LOCALIZATION_ID_RATE_30_SECONDS,
	"40 segundos", // LOCALIZATION_ID_RATE_40_SECONDS,
	"50 segundos", // LOCALIZATION_ID_RATE_50_SECONDS,
	"1 minuto",	// LOCALIZATION_ID_RATE_1_MINUTE,
	"Personalizado...", // LOCALIZATION_ID_CUSTOM,
	"&Duración de animación", // LOCALIZATION_ID_RATE_ANIMATION_DURATION,
	
	// Animation menu
	"&Animación", // LOCALIZATION_ID_ANIMATION,
	"&Reproducir/Pausar", // LOCALIZATION_ID_ANIMATION_PLAY_PAUSE,
	"Saltar &adelante", // LOCALIZATION_ID_ANIMATION_JUMP_FORWARD,
	"Saltar &atrás", // LOCALIZATION_ID_ANIMATION_JUMP_BACKWARD,
	"Salto corto &adelante", // LOCALIZATION_ID_ANIMATION_SHORT_JUMP_FORWARD,
	"Salto corto &atrás", // LOCALIZATION_ID_ANIMATION_SHORT_JUMP_BACKWARD,
	"Salto largo &adelante", // LOCALIZATION_ID_ANIMATION_LONG_JUMP_FORWARD,
	"Salto largo &atrás", // LOCALIZATION_ID_ANIMATION_LONG_JUMP_BACKWARD,
	"&Paso de fotograma", // LOCALIZATION_ID_ANIMATION_FRAME_STEP,
	"Fotograma &anterior", // LOCALIZATION_ID_ANIMATION_PREVIOUS_FRAME,
	"&Primer fotograma", // LOCALIZATION_ID_ANIMATION_FIRST_FRAME,
	"&Último fotograma", // LOCALIZATION_ID_ANIMATION_LAST_FRAME,
	"&Disminuir velocidad", // LOCALIZATION_ID_ANIMATION_DECREASE_RATE,
	"&Aumentar velocidad", // LOCALIZATION_ID_ANIMATION_INCREASE_RATE,
	"&Restablecer velocidad", // LOCALIZATION_ID_ANIMATION_RESET_RATE,
	
	// Navigate menu
	"&Navegar", // LOCALIZATION_ID_NAVIGATE,
	"&Siguiente", // LOCALIZATION_ID_NEXT,
	"&Anterior", // LOCALIZATION_ID_PREVIOUS,
	"&Inicio", // LOCALIZATION_ID_HOME,
	"&Fin", // LOCALIZATION_ID_END,
	"&Ordenar", // LOCALIZATION_ID_SORT,
	"&Nombre", // LOCALIZATION_ID_SORT_NAME,
	"&Ruta completa", // LOCALIZATION_ID_SORT_FULL_PATH,
	"&Tamaño", // LOCALIZATION_ID_SORT_SIZE,
	"Fecha de &modificación", // LOCALIZATION_ID_SORT_DATE_MODIFIED,
	"Fecha de &creación", // LOCALIZATION_ID_SORT_DATE_CREATED,
	"&Ascendente", // LOCALIZATION_ID_SORT_ASCENDING,
	"&Descendente", // LOCALIZATION_ID_SORT_DESCENDING,
	"Mezclar", // LOCALIZATION_ID_SHUFFLE,
	"&Ir a...", // LOCALIZATION_ID_JUMP_TO,
	
	// Help menu
	"Ay&uda", // LOCALIZATION_ID_HELP,
	"Ay&uda", // LOCALIZATION_ID_HELP_MENU,
	"&Opciones de línea de comandos", // LOCALIZATION_ID_COMMAND_LINE_OPTIONS,
	"&Página de inicio", // LOCALIZATION_ID_HOME_PAGE,
	"&Donar", // LOCALIZATION_ID_DONATE,
	"&Acerca de", // LOCALIZATION_ID_ABOUT,
	"https://www.voidtools.com/support/voidimageviewer/", // LOCALIZATION_ID_HELP_SUPPORT_URL,
	"https://www.voidtools.com/donate/", // LOCALIZATION_ID_HELP_DONATE_URL,
	"https://www.voidtools.com/", // LOCALIZATION_ID_HELP_WEBSITE_URL,

	// Toolbar
	"Imagen anterior", // LOCALIZATION_ID_TOOLBAR_PREVIOUS_IMAGE_BUTTON,
	"Imagen siguiente", // LOCALIZATION_ID_TOOLBAR_NEXT_IMAGE_BUTTON,
	"Reproducir diapositivas", // LOCALIZATION_ID_TOOLBAR_PLAY_SLIDESHOW_BUTTON,
	"Pausar diapositivas", // LOCALIZATION_ID_TOOLBAR_PAUSE_SLIDESHOW_BUTTON,
	"Mejor ajuste", // LOCALIZATION_ID_TOOLBAR_BEST_FIT_BUTTON,
	"Tamaño real", // LOCALIZATION_ID_TOOLBAR_ACTUAL_SIZE_BUTTON,

	// Status bar
	"PRELOAD", // LOCALIZATION_ID_STATUS_BAR_PRELOAD,
	"Cargando...", // LOCALIZATION_ID_STATUS_BAR_LOADING,
	"Archivo no encontrado.", // LOCALIZATION_ID_STATUS_BAR_FILE_NOT_FOUND,
	"No se pudo cargar la imagen.", // LOCALIZATION_ID_STATUS_BAR_FAILED_TO_LOAD_IMAGE,
	"Diapositivas en reproducción", // LOCALIZATION_ID_STATUS_BAR_SLIDESHOW_PLAYING,
	"Pos %0.3f %0.3f, Zoom %0.3f %0.3f, Proporción %0.3f", // LOCALIZATION_ID_STATUS_BAR_POS_ZOOM_FORMAT,
	"Velocidad de animación %0.3f", // LOCALIZATION_ID_STATUS_BAR_ANIMATION_RATE_FORMAT,
	"Velocidad de diapositivas %d %s", // LOCALIZATION_ID_STATUS_BAR_SLIDESHOW_RATE_FORMAT,
	"Velocidad de diapositivas: duración de animación", // LOCALIZATION_ID_STATUS_BAR_ANIMATION_DURATION,
	"minutos", // LOCALIZATION_ID_STATUS_BAR_MINUTES,
	"segundos", // LOCALIZATION_ID_STATUS_BAR_SECONDS,
	"milisegundos", // LOCALIZATION_ID_STATUS_BAR_MILLISECONDS,

	// Dialog strings
	"Opciones - void Image Viewer", // LOCALIZATION_ID_OPTIONS_CAPTION,
	"General", // LOCALIZATION_ID_OPTIONS_GENERAL_DIALOG,
	"Ver", // LOCALIZATION_ID_OPTIONS_VIEW_DIALOG,
	"Controles", // LOCALIZATION_ID_OPTIONS_CONTROLS_DIALOG,
	"Aceptar", // LOCALIZATION_ID_OK_BUTTON,
	"Cancelar", // LOCALIZATION_ID_CANCEL_BUTTON,
	"&Guardar configuración en %APPDATA%\\voidImageViewer", // LOCALIZATION_ID_STORE_SETTINGS_APPDATA,
	"Permitir varias &instancias", // LOCALIZATION_ID_ALLOW_MULTIPLE_INSTANCES,
	"Accesos directos del &menú Inicio", // LOCALIZATION_ID_STARTMENU_SHORTCUTS,
	"Asociaciones", // LOCALIZATION_ID_ASSOCIATIONS,
	"Marcar &todo", // LOCALIZATION_ID_CHECK_ALL,
	"Desmarcar &todo", // LOCALIZATION_ID_CHECK_NONE,
	"Modo de blit de &reducción:", // LOCALIZATION_ID_SHRINK_BLIT_MODE_STATIC,
	"Modo de blit de &ampliación:", // LOCALIZATION_ID_MAGNIFY_BLIT_MODE,
	"Vecino más cercano", // LOCALIZATION_ID_BLIT_MODE_NEAREST_COMBOBOXITEM,
	"Lineal", // LOCALIZATION_ID_BLIT_MODE_LINEAR_COMBOBOXITEM,
	"&Tamaño automático de ventana:", // LOCALIZATION_ID_OPTIONS_VIEW_AUTO_SIZE_WINDOW_STATIC,
	"50%", // LOCALIZATION_ID_OPTIONS_VIEW_AUTO_SIZE_WINDOW_50_PERCENT_COMBOBOXITEM,
	"100%", // LOCALIZATION_ID_OPTIONS_VIEW_AUTO_SIZE_WINDOW_100_PERCENT_COMBOBOXITEM,
	"200%", // LOCALIZATION_ID_OPTIONS_VIEW_AUTO_SIZE_WINDOW_200_PERCENT_COMBOBOXITEM,
	"Ajuste automático", // LOCALIZATION_ID_OPTIONS_VIEW_AUTO_SIZE_WINDOW_AUTO_FIT_COMBOBOXITEM,
	"&Reproducir animaciones al menos una vez en diapositivas", // LOCALIZATION_ID_PLAY_ANIMATIONS_ONCE_STATIC,
	"Precargar imagen &siguiente", // LOCALIZATION_ID_PRELOAD_NEXT_IMAGE_STATIC,
	"Almacenar en caché la &última imagen", // LOCALIZATION_ID_CACHE_LAST_IMAGE_STATIC,
	"Color de fondo en &ventana:", // LOCALIZATION_ID_WINDOWED_BACKGROUND_COLOR_STATIC,
	"Color de fondo en &pantalla completa:", // LOCALIZATION_ID_FULLSCREEN_BACKGROUND_COLOR_STATIC,
	"Acción del clic &izquierdo:", // LOCALIZATION_ID_LEFT_CLICK_ACTION_STATIC,
	"Acción del clic &derecho:", // LOCALIZATION_ID_RIGHT_CLICK_ACTION_STATIC,
	"Acción de la &rueda del mouse:", // LOCALIZATION_ID_MOUSE_WHEEL_ACTION_STATIC,
	"&Comandos:", // LOCALIZATION_ID_COMMANDS_STATIC,
	"Configuración del comando seleccionado", // LOCALIZATION_ID_SETTINGS_FOR_SELECTED_COMMAND,
	"&Agregar...", // LOCALIZATION_ID_ADD_KEY_BUTTON,
	"&Editar...", // LOCALIZATION_ID_EDIT_KEY_BUTTON,
	"&Quitar", // LOCALIZATION_ID_REMOVE_KEY_BUTTON,
	"Agregar acceso directo de teclado", // LOCALIZATION_ID_ADD_KEYBOARD_SHORTCUT_CAPTION,
	"Editar acceso directo de teclado", // LOCALIZATION_ID_EDIT_KEYBOARD_SHORTCUT_CAPTION,
	"&Tecla de acceso directo:", // LOCALIZATION_ID_SHORTCUT_KEY,
	"Tecla de acceso directo utilizada actualmente por:", // LOCALIZATION_ID_SHORTCUT_KEY_CURRENTLY_USED_BY,
	"Establecer velocidad personalizada", // LOCALIZATION_ID_SET_CUSTOM_RATE_CAPTION,
	"&Velocidad personalizada:", // LOCALIZATION_ID_CUSTOM_RATE_STATIC,
	"minutos", // LOCALIZATION_ID_CUSTOM_RATE_MINUTES,
	"segundos", // LOCALIZATION_ID_CUSTOM_RATE_SECONDS,
	"milisegundos", // LOCALIZATION_ID_CUSTOM_RATE_MILLISECONDS,
	"Acerca de void Image Viewer", // LOCALIZATION_ID_ABOUT_CAPTION,
	"Renombrar", // LOCALIZATION_ID_RENAME_CAPTION,
	"Ir a", // LOCALIZATION_ID_JUMP_TO_TITLE,
	"Copyright © %d voidtools", // LOCALIZATION_ID_ABOUT_COPYRIGHT_FORMAT,
	"support@voidtools.com", // LOCALIZATION_ID_ABOUT_EMAIL,
	"www.voidtools.com", // LOCALIZATION_ID_ABOUT_WEBSITE,
	"Abrir imagen", // LOCALIZATION_ID_OPEN_IMAGE_CAPTION,
	"Todos los archivos de imagen", // LOCALIZATION_ID_OPEN_ALL_IMAGE_FILES,
	"Todos los archivos", // LOCALIZATION_ID_OPEN_ALL_FILES,
	"Desplazar", // LOCALIZATION_ID_OPTIONS_ACTION_SCROLL_COMBOBOXITEM,
	"Reproducir/Pausar diapositivas", // LOCALIZATION_ID_OPTIONS_ACTION_PLAY_PAUSE_SLIDESHOW_COMBOBOXITEM,
	"Reproducir/Pausar animación", // LOCALIZATION_ID_OPTIONS_ACTION_PLAY_PAUSE_ANIMATION_COMBOBOXITEM,
	"Zoom adentro", // LOCALIZATION_ID_OPTIONS_ACTION_ZOOM_IN_COMBOBOXITEM,
	"Imagen siguiente", // LOCALIZATION_ID_OPTIONS_ACTION_NEXT_IMAGE_COMBOBOXITEM,
	"Desplazamiento 1:1", // LOCALIZATION_ID_OPTIONS_ACTION_ONE_TO_ONE_SCROLL_COMBOBOXITEM,
	"Desplazar/Mover ventana", // LOCALIZATION_ID_OPTIONS_ACTION_SCROLL_MOVE_WINDOW_COMBOBOXITEM,
	"Menú contextual", // LOCALIZATION_ID_OPTIONS_ACTION_CONTEXT_MENU_COMBOBOXITEM,
	"Zoom afuera", // LOCALIZATION_ID_OPTIONS_ACTION_ZOOM_OUT_COMBOBOXITEM,
	"Imagen anterior", // LOCALIZATION_ID_OPTIONS_ACTION_PREVIOUS_IMAGE_COMBOBOXITEM,
	"Zoom", // LOCALIZATION_ID_OPTIONS_ACTION_ZOOM_COMBOBOXITEM,
	"Siguiente/Anterior", // LOCALIZATION_ID_OPTIONS_ACTION_NEXT_PREV_COMBOBOXITEM,
	"Anterior/Siguiente", // LOCALIZATION_ID_OPTIONS_ACTION_PREV_NEXT_COMBOBOXITEM,
	"&Formato de barra de título:", // LOCALIZATION_ID_OPTIONS_TITLE_BAR_FORMAT_STATIC,
	"Ruta completa", // LOCALIZATION_ID_OPTIONS_TITLE_BAR_FORMAT_FULL_PATH_COMBOBOXITEM,
	"Solo nombre de archivo", // LOCALIZATION_ID_OPTIONS_TITLE_BAR_FORMAT_FILENAME_ONLY_COMBOBOXITEM,
	"Ninguno", // LOCALIZATION_ID_OPTIONS_TITLE_BAR_FORMAT_NONE_COMBOBOXITEM,
	"Everything no está disponible", // LOCALIZATION_ID_EVERYTHING_NOT_AVAILABLE_MESSAGE,
	"Agregar búsqueda de Everything", // LOCALIZATION_ID_EVERYTHING_ADD_EVERYTHING_SEARCH_CAPTION,
	"Cargar búsqueda de Everything", // LOCALIZATION_ID_EVERYTHING_LOAD_EVERYTHING_SEARCH_CAPTION,
	"Aleatorio", // LOCALIZATION_ID_RANDOMIZE,
	"Copiar a", // LOCALIZATION_ID_COPY_TO_CAPTION,
	"Mover a", // LOCALIZATION_ID_MOVE_TO_CAPTION,

	// Association descriptions
	"Imagen de mapa de bits",
	"Imagen GIF animada",
	"Imagen HEIC",
	"Imagen HEIF",
	"Archivo de icono",
	"Imagen JPEG",
	"Imagen JPEG",
	"Imagen PNG",
	"Imagen TIFF",
	"Imagen TIFF",
	"Imagen WebP",
};
