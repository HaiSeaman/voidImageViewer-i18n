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
// Italiano localization
// Save as UTF-8 with BOM (required for MSVC to parse non-ASCII correctly).

static const utf8_t *_localization_string_array_it[LOCALIZATION_ID_COUNT] = 
{
	// Application name
	"Italiano", // LOCALIZATION_ID_LANGUAGE

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
	"&File", // LOCALIZATION_ID_FILE,
	"&Apri file...", // LOCALIZATION_ID_OPEN_FILE,
	"Apri &cartella...", // LOCALIZATION_ID_OPEN_FOLDER,
	"Apri &ricerca Everything...", // LOCALIZATION_ID_OPEN_EVERYTHING_SEARCH,
	"&Aggiungi file...", // LOCALIZATION_ID_ADD_FILE,
	"Aggiungi cartella...", // LOCALIZATION_ID_ADD_FOLDER,
	"Aggiungi ricerca Everything...", // LOCALIZATION_ID_ADD_EVERYTHING_SEARCH,
	"Apri &posizione del file...", // LOCALIZATION_ID_OPEN_FILE_LOCATION,
	"&Modifica...", // LOCALIZATION_ID_EDIT,
	"&Anteprima...", // LOCALIZATION_ID_PREVIEW,
	"&Stampa...", // LOCALIZATION_ID_PRINT,
	"Imposta come sfondo del &desktop", // LOCALIZATION_ID_SET_DESKTOP_WALLPAPER,
	"&Chiudi", // LOCALIZATION_ID_CLOSE,
	"&Elimina", // LOCALIZATION_ID_DELETE,
	"Elimina (Cestino)", // LOCALIZATION_ID_DELETE_RECYCLE,
	"Elimina (Definitivamente)", // LOCALIZATION_ID_DELETE_PERMANENTLY,
	"&Rinomina", // LOCALIZATION_ID_RENAME,
	"&Proprietà", // LOCALIZATION_ID_PROPERTIES,
	"&Esci", // LOCALIZATION_ID_EXIT,
	
	// Edit menu
	"&Modifica", // LOCALIZATION_ID_EDIT_MENU,
	"&Taglia", // LOCALIZATION_ID_CUT,
	"&Copia", // LOCALIZATION_ID_COPY,
	"Copia nome file", // LOCALIZATION_ID_COPY_FILENAME,
	"Copia &immagine", // LOCALIZATION_ID_COPY_IMAGE,
	"&Incolla", // LOCALIZATION_ID_PASTE,
	"Ruota in senso &orario", // LOCALIZATION_ID_ROTATE_CLOCKWISE,
	"Ruota in senso &antiorario", // LOCALIZATION_ID_ROTATE_COUNTERCLOCKWISE,
	"Copia in &cartella...", // LOCALIZATION_ID_COPY_TO,
	"&Sposta in cartella...", // LOCALIZATION_ID_MOVE_TO,
	
	// View menu
	"&Visualizza", // LOCALIZATION_ID_VIEW,
	"Didascalia", // LOCALIZATION_ID_CAPTION,
	"Cornice", // LOCALIZATION_ID_FRAME,
	"&Menu", // LOCALIZATION_ID_MENU,
	"&Barra di stato", // LOCALIZATION_ID_STATUS_BAR,
	"&Controlli", // LOCALIZATION_ID_CONTROLS,
	"&Preimpostazione", // LOCALIZATION_ID_PRESET,
	"&Minimo", // LOCALIZATION_ID_MINIMAL,
	"&Compatto", // LOCALIZATION_ID_COMPACT,
	"&Normale", // LOCALIZATION_ID_NORMAL,
	"&Schermo intero", // LOCALIZATION_ID_FULLSCREEN,
	"&Presentazione", // LOCALIZATION_ID_SLIDESHOW,
	"&Dimensione finestra", // LOCALIZATION_ID_VIEW_WINDOW_SIZE,
	"50%", // LOCALIZATION_ID_VIEW_WINDOW_SIZE_50_PERCENT,
	"100%", // LOCALIZATION_ID_VIEW_WINDOW_SIZE_100_PERCENT,
	"200%", // LOCALIZATION_ID_VIEW_WINDOW_SIZE_200_PERCENT,
	"&Adattamento automatico", // LOCALIZATION_ID_VIEW_WINDOW_SIZE_AUTO_FIT,
	"&Aggiorna", // LOCALIZATION_ID_REFRESH,
	"&Consenti riduzione", // LOCALIZATION_ID_ALLOW_SHRINKING,
	"&Mantieni proporzioni", // LOCALIZATION_ID_KEEP_ASPECT_RATIO,
	"&Riempi finestra", // LOCALIZATION_ID_FILL_WINDOW,
	"1:1", // LOCALIZATION_ID_ONE_TO_ONE,
	"&Adattamento ottimale", // LOCALIZATION_ID_BEST_FIT,
	"&Panoramica && scansione", // LOCALIZATION_ID_PAN_SCAN,
	"&Aumenta dimensione", // LOCALIZATION_ID_INCREASE_SIZE,
	"&Diminuisci dimensione", // LOCALIZATION_ID_DECREASE_SIZE,
	"A&umenta larghezza", // LOCALIZATION_ID_INCREASE_WIDTH,
	"D&iminuisci larghezza", // LOCALIZATION_ID_DECREASE_WIDTH,
	"Aumenta &altezza", // LOCALIZATION_ID_INCREASE_HEIGHT,
	"Diminuisci &altezza", // LOCALIZATION_ID_DECREASE_HEIGHT,
	"&Zoom", // LOCALIZATION_ID_ZOOM,
	"Zoom &avanti", // LOCALIZATION_ID_ZOOM_IN,
	"Zoom &indietro", // LOCALIZATION_ID_ZOOM_OUT,
	"&Reimposta", // LOCALIZATION_ID_RESET,
	"Sposta &su", // LOCALIZATION_ID_MOVE_UP,
	"Sposta &giù", // LOCALIZATION_ID_MOVE_DOWN,
	"Sposta a &sinistra", // LOCALIZATION_ID_MOVE_LEFT,
	"Sposta a &destra", // LOCALIZATION_ID_MOVE_RIGHT,
	"Sposta in alto a sinistra", // LOCALIZATION_ID_MOVE_UP_LEFT,
	"Sposta in alto a destra", // LOCALIZATION_ID_MOVE_UP_RIGHT,
	"Sposta in basso a sinistra", // LOCALIZATION_ID_MOVE_DOWN_LEFT,
	"Sposta in basso a destra", // LOCALIZATION_ID_MOVE_DOWN_RIGHT,
	"Sposta al &centro", // LOCALIZATION_ID_MOVE_CENTER,
	"Re&imposta", // LOCALIZATION_ID_PANSCAN_RESET,
	"Sempre in &primo piano", // LOCALIZATION_ID_ON_TOP,
	"&Sempre", // LOCALIZATION_ID_ALWAYS,
	"&Durante presentazione o animazione", // LOCALIZATION_ID_WHILE_PLAYING_OR_ANIMATING,
	"&Mai", // LOCALIZATION_ID_NEVER,
	"&Opzioni...", // LOCALIZATION_ID_OPTIONS,
	"&Transizione", // LOCALIZATION_ID_TRANSITION,
	"&Nessuna", // LOCALIZATION_ID_TRANSITION_NONE,
	"&Dissolvenza", // LOCALIZATION_ID_TRANSITION_FADE,
	"Durata...", // LOCALIZATION_ID_TRANSITION_DURATION,
	"Imposta durata transizione", // LOCALIZATION_ID_SET_TRANSITION_DURATION_CAPTION,
	"&Durata (ms):", // LOCALIZATION_ID_TRANSITION_DURATION_STATIC,
	"&Mostra interfaccia al passaggio del mouse", // LOCALIZATION_ID_HOVER_SHOW_UI,
	
	// Slideshow menu
	"&Presentazione", // LOCALIZATION_ID_SLIDESHOW_MENU,
	"&Riproduci/Pausa", // LOCALIZATION_ID_PLAY_PAUSE,
	"&Velocità", // LOCALIZATION_ID_RATE,
	"&Diminuisci velocità", // LOCALIZATION_ID_DECREASE_RATE,
	"&Aumenta velocità", // LOCALIZATION_ID_INCREASE_RATE,
	"250 millisecondi", // LOCALIZATION_ID_RATE_250_MILLISECONDS,
	"500 millisecondi", // LOCALIZATION_ID_RATE_500_MILLISECONDS,
	"&1 secondo", // LOCALIZATION_ID_RATE_1_SECOND,
	"&2 secondi", // LOCALIZATION_ID_RATE_2_SECONDS,
	"&3 secondi", // LOCALIZATION_ID_RATE_3_SECONDS,
	"&4 secondi", // LOCALIZATION_ID_RATE_4_SECONDS,
	"&5 secondi", // LOCALIZATION_ID_RATE_5_SECONDS,
	"&6 secondi", // LOCALIZATION_ID_RATE_6_SECONDS,
	"&7 secondi", // LOCALIZATION_ID_RATE_7_SECONDS,
	"&8 secondi", // LOCALIZATION_ID_RATE_8_SECONDS,
	"&9 secondi", // LOCALIZATION_ID_RATE_9_SECONDS,
	"1&0 secondi", // LOCALIZATION_ID_RATE_10_SECONDS,
	"20 secondi", // LOCALIZATION_ID_RATE_20_SECONDS,
	"30 secondi", // LOCALIZATION_ID_RATE_30_SECONDS,
	"40 secondi", // LOCALIZATION_ID_RATE_40_SECONDS,
	"50 secondi", // LOCALIZATION_ID_RATE_50_SECONDS,
	"1 minuto",	// LOCALIZATION_ID_RATE_1_MINUTE,
	"Personalizzato...", // LOCALIZATION_ID_CUSTOM,
	"&Durata animazione", // LOCALIZATION_ID_RATE_ANIMATION_DURATION,
	
	// Animation menu
	"&Animazione", // LOCALIZATION_ID_ANIMATION,
	"&Riproduci/Pausa", // LOCALIZATION_ID_ANIMATION_PLAY_PAUSE,
	"Salta &avanti", // LOCALIZATION_ID_ANIMATION_JUMP_FORWARD,
	"Salta &indietro", // LOCALIZATION_ID_ANIMATION_JUMP_BACKWARD,
	"Salto breve &avanti", // LOCALIZATION_ID_ANIMATION_SHORT_JUMP_FORWARD,
	"Salto breve &indietro", // LOCALIZATION_ID_ANIMATION_SHORT_JUMP_BACKWARD,
	"Salto lungo &avanti", // LOCALIZATION_ID_ANIMATION_LONG_JUMP_FORWARD,
	"Salto lungo &indietro", // LOCALIZATION_ID_ANIMATION_LONG_JUMP_BACKWARD,
	"&Passo fotogramma", // LOCALIZATION_ID_ANIMATION_FRAME_STEP,
	"Fotogramma &precedente", // LOCALIZATION_ID_ANIMATION_PREVIOUS_FRAME,
	"&Primo fotogramma", // LOCALIZATION_ID_ANIMATION_FIRST_FRAME,
	"&Ultimo fotogramma", // LOCALIZATION_ID_ANIMATION_LAST_FRAME,
	"&Diminuisci velocità", // LOCALIZATION_ID_ANIMATION_DECREASE_RATE,
	"&Aumenta velocità", // LOCALIZATION_ID_ANIMATION_INCREASE_RATE,
	"&Reimposta velocità", // LOCALIZATION_ID_ANIMATION_RESET_RATE,
	
	// Navigate menu
	"&Naviga", // LOCALIZATION_ID_NAVIGATE,
	"&Successivo", // LOCALIZATION_ID_NEXT,
	"&Precedente", // LOCALIZATION_ID_PREVIOUS,
	"&Inizio", // LOCALIZATION_ID_HOME,
	"&Fine", // LOCALIZATION_ID_END,
	"&Ordina", // LOCALIZATION_ID_SORT,
	"&Nome", // LOCALIZATION_ID_SORT_NAME,
	"&Percorso completo", // LOCALIZATION_ID_SORT_FULL_PATH,
	"&Dimensione", // LOCALIZATION_ID_SORT_SIZE,
	"Data di &modifica", // LOCALIZATION_ID_SORT_DATE_MODIFIED,
	"Data di &creazione", // LOCALIZATION_ID_SORT_DATE_CREATED,
	"&Crescente", // LOCALIZATION_ID_SORT_ASCENDING,
	"&Decrescente", // LOCALIZATION_ID_SORT_DESCENDING,
	"Miscela", // LOCALIZATION_ID_SHUFFLE,
	"&Vai a...", // LOCALIZATION_ID_JUMP_TO,
	
	// Help menu
	"&Aiuto", // LOCALIZATION_ID_HELP,
	"&Aiuto", // LOCALIZATION_ID_HELP_MENU,
	"&Opzioni riga di comando", // LOCALIZATION_ID_COMMAND_LINE_OPTIONS,
	"&Pagina iniziale", // LOCALIZATION_ID_HOME_PAGE,
	"&Dona", // LOCALIZATION_ID_DONATE,
	"&Informazioni", // LOCALIZATION_ID_ABOUT,
	"https://www.voidtools.com/support/voidimageviewer/", // LOCALIZATION_ID_HELP_SUPPORT_URL,
	"https://www.voidtools.com/donate/", // LOCALIZATION_ID_HELP_DONATE_URL,
	"https://www.voidtools.com/", // LOCALIZATION_ID_HELP_WEBSITE_URL,

	// Toolbar
	"Immagine precedente", // LOCALIZATION_ID_TOOLBAR_PREVIOUS_IMAGE_BUTTON,
	"Immagine successiva", // LOCALIZATION_ID_TOOLBAR_NEXT_IMAGE_BUTTON,
	"Riproduci presentazione", // LOCALIZATION_ID_TOOLBAR_PLAY_SLIDESHOW_BUTTON,
	"Metti in pausa presentazione", // LOCALIZATION_ID_TOOLBAR_PAUSE_SLIDESHOW_BUTTON,
	"Adattamento ottimale", // LOCALIZATION_ID_TOOLBAR_BEST_FIT_BUTTON,
	"Dimensione reale", // LOCALIZATION_ID_TOOLBAR_ACTUAL_SIZE_BUTTON,

	// Status bar
	"PRELOAD", // LOCALIZATION_ID_STATUS_BAR_PRELOAD,
	"Caricamento...", // LOCALIZATION_ID_STATUS_BAR_LOADING,
	"File non trovato.", // LOCALIZATION_ID_STATUS_BAR_FILE_NOT_FOUND,
	"Impossibile caricare l'immagine.", // LOCALIZATION_ID_STATUS_BAR_FAILED_TO_LOAD_IMAGE,
	"Presentazione in riproduzione", // LOCALIZATION_ID_STATUS_BAR_SLIDESHOW_PLAYING,
	"Pos %0.3f %0.3f, Zoom %0.3f %0.3f, Proporzioni %0.3f", // LOCALIZATION_ID_STATUS_BAR_POS_ZOOM_FORMAT,
	"Velocità animazione %0.3f", // LOCALIZATION_ID_STATUS_BAR_ANIMATION_RATE_FORMAT,
	"Velocità presentazione %d %s", // LOCALIZATION_ID_STATUS_BAR_SLIDESHOW_RATE_FORMAT,
	"Velocità presentazione: durata animazione", // LOCALIZATION_ID_STATUS_BAR_ANIMATION_DURATION,
	"minuti", // LOCALIZATION_ID_STATUS_BAR_MINUTES,
	"secondi", // LOCALIZATION_ID_STATUS_BAR_SECONDS,
	"millisecondi", // LOCALIZATION_ID_STATUS_BAR_MILLISECONDS,

	// Dialog strings
	"Opzioni - void Image Viewer", // LOCALIZATION_ID_OPTIONS_CAPTION,
	"Generale", // LOCALIZATION_ID_OPTIONS_GENERAL_DIALOG,
	"Visualizza", // LOCALIZATION_ID_OPTIONS_VIEW_DIALOG,
	"Controlli", // LOCALIZATION_ID_OPTIONS_CONTROLS_DIALOG,
	"OK", // LOCALIZATION_ID_OK_BUTTON,
	"Annulla", // LOCALIZATION_ID_CANCEL_BUTTON,
	"&Salva impostazioni in %APPDATA%\\voidImageViewer", // LOCALIZATION_ID_STORE_SETTINGS_APPDATA,
	"Consenti più &istanze", // LOCALIZATION_ID_ALLOW_MULTIPLE_INSTANCES,
	"Collegamenti del &menu Start", // LOCALIZATION_ID_STARTMENU_SHORTCUTS,
	"Associazioni", // LOCALIZATION_ID_ASSOCIATIONS,
	"Seleziona &tutto", // LOCALIZATION_ID_CHECK_ALL,
	"Deseleziona &tutto", // LOCALIZATION_ID_CHECK_NONE,
	"Modalità blit di &riduzione:", // LOCALIZATION_ID_SHRINK_BLIT_MODE_STATIC,
	"Modalità blit di &ingrandimento:", // LOCALIZATION_ID_MAGNIFY_BLIT_MODE,
	"Vicino più prossimo", // LOCALIZATION_ID_BLIT_MODE_NEAREST_COMBOBOXITEM,
	"Lineare", // LOCALIZATION_ID_BLIT_MODE_LINEAR_COMBOBOXITEM,
	"&Dimensione automatica finestra:", // LOCALIZATION_ID_OPTIONS_VIEW_AUTO_SIZE_WINDOW_STATIC,
	"50%", // LOCALIZATION_ID_OPTIONS_VIEW_AUTO_SIZE_WINDOW_50_PERCENT_COMBOBOXITEM,
	"100%", // LOCALIZATION_ID_OPTIONS_VIEW_AUTO_SIZE_WINDOW_100_PERCENT_COMBOBOXITEM,
	"200%", // LOCALIZATION_ID_OPTIONS_VIEW_AUTO_SIZE_WINDOW_200_PERCENT_COMBOBOXITEM,
	"Adattamento automatico", // LOCALIZATION_ID_OPTIONS_VIEW_AUTO_SIZE_WINDOW_AUTO_FIT_COMBOBOXITEM,
	"&Riproduci animazioni almeno una volta nella presentazione", // LOCALIZATION_ID_PLAY_ANIMATIONS_ONCE_STATIC,
	"Precarica immagine &successiva", // LOCALIZATION_ID_PRELOAD_NEXT_IMAGE_STATIC,
	"Memorizza nella cache l'&ultima immagine", // LOCALIZATION_ID_CACHE_LAST_IMAGE_STATIC,
	"Colore di sfondo in &finestra:", // LOCALIZATION_ID_WINDOWED_BACKGROUND_COLOR_STATIC,
	"Colore di sfondo a &schermo intero:", // LOCALIZATION_ID_FULLSCREEN_BACKGROUND_COLOR_STATIC,
	"Azione del clic &sinistro:", // LOCALIZATION_ID_LEFT_CLICK_ACTION_STATIC,
	"Azione del clic &destro:", // LOCALIZATION_ID_RIGHT_CLICK_ACTION_STATIC,
	"Azione della &rotella del mouse:", // LOCALIZATION_ID_MOUSE_WHEEL_ACTION_STATIC,
	"&Comandi:", // LOCALIZATION_ID_COMMANDS_STATIC,
	"Impostazioni per il comando selezionato", // LOCALIZATION_ID_SETTINGS_FOR_SELECTED_COMMAND,
	"&Aggiungi...", // LOCALIZATION_ID_ADD_KEY_BUTTON,
	"&Modifica...", // LOCALIZATION_ID_EDIT_KEY_BUTTON,
	"&Rimuovi", // LOCALIZATION_ID_REMOVE_KEY_BUTTON,
	"Aggiungi scorciatoia da tastiera", // LOCALIZATION_ID_ADD_KEYBOARD_SHORTCUT_CAPTION,
	"Modifica scorciatoia da tastiera", // LOCALIZATION_ID_EDIT_KEYBOARD_SHORTCUT_CAPTION,
	"&Tasto di scelta rapida:", // LOCALIZATION_ID_SHORTCUT_KEY,
	"Tasto di scelta rapida attualmente usato da:", // LOCALIZATION_ID_SHORTCUT_KEY_CURRENTLY_USED_BY,
	"&Rimuovi", // LOCALIZATION_ID_REMOVE,
	"Imposta velocità personalizzata", // LOCALIZATION_ID_SET_CUSTOM_RATE_CAPTION,
	"&Velocità personalizzata:", // LOCALIZATION_ID_CUSTOM_RATE_STATIC,
	"minuti", // LOCALIZATION_ID_CUSTOM_RATE_MINUTES,
	"secondi", // LOCALIZATION_ID_CUSTOM_RATE_SECONDS,
	"millisecondi", // LOCALIZATION_ID_CUSTOM_RATE_MILLISECONDS,
	"Informazioni su void Image Viewer", // LOCALIZATION_ID_ABOUT_CAPTION,
	"Rinomina", // LOCALIZATION_ID_RENAME_CAPTION,
	"Vai a", // LOCALIZATION_ID_JUMP_TO_TITLE,
	"Cerca in Everything", // LOCALIZATION_ID_SEARCH_EVERYTHING,
	"Copyright © %d voidtools", // LOCALIZATION_ID_ABOUT_COPYRIGHT_FORMAT,
	"support@voidtools.com", // LOCALIZATION_ID_ABOUT_EMAIL,
	"www.voidtools.com", // LOCALIZATION_ID_ABOUT_WEBSITE,
	"Apri immagine", // LOCALIZATION_ID_OPEN_IMAGE_CAPTION,
	"Tutti i file immagine", // LOCALIZATION_ID_OPEN_ALL_IMAGE_FILES,
	"Tutti i file", // LOCALIZATION_ID_OPEN_ALL_FILES,
	"Scorri", // LOCALIZATION_ID_OPTIONS_ACTION_SCROLL_COMBOBOXITEM,
	"Riproduci/Pausa presentazione", // LOCALIZATION_ID_OPTIONS_ACTION_PLAY_PAUSE_SLIDESHOW_COMBOBOXITEM,
	"Riproduci/Pausa animazione", // LOCALIZATION_ID_OPTIONS_ACTION_PLAY_PAUSE_ANIMATION_COMBOBOXITEM,
	"Zoom avanti", // LOCALIZATION_ID_OPTIONS_ACTION_ZOOM_IN_COMBOBOXITEM,
	"Immagine successiva", // LOCALIZATION_ID_OPTIONS_ACTION_NEXT_IMAGE_COMBOBOXITEM,
	"Scorrimento 1:1", // LOCALIZATION_ID_OPTIONS_ACTION_ONE_TO_ONE_SCROLL_COMBOBOXITEM,
	"Scorri/Sposta finestra", // LOCALIZATION_ID_OPTIONS_ACTION_SCROLL_MOVE_WINDOW_COMBOBOXITEM,
	"Menu contestuale", // LOCALIZATION_ID_OPTIONS_ACTION_CONTEXT_MENU_COMBOBOXITEM,
	"Zoom indietro", // LOCALIZATION_ID_OPTIONS_ACTION_ZOOM_OUT_COMBOBOXITEM,
	"Immagine precedente", // LOCALIZATION_ID_OPTIONS_ACTION_PREVIOUS_IMAGE_COMBOBOXITEM,
	"Zoom", // LOCALIZATION_ID_OPTIONS_ACTION_ZOOM_COMBOBOXITEM,
	"Successivo/Precedente", // LOCALIZATION_ID_OPTIONS_ACTION_NEXT_PREV_COMBOBOXITEM,
	"Precedente/Successivo", // LOCALIZATION_ID_OPTIONS_ACTION_PREV_NEXT_COMBOBOXITEM,
	"&Formato barra del titolo:", // LOCALIZATION_ID_OPTIONS_TITLE_BAR_FORMAT_STATIC,
	"Percorso completo", // LOCALIZATION_ID_OPTIONS_TITLE_BAR_FORMAT_FULL_PATH_COMBOBOXITEM,
	"Solo nome file", // LOCALIZATION_ID_OPTIONS_TITLE_BAR_FORMAT_FILENAME_ONLY_COMBOBOXITEM,
	"Nessuno", // LOCALIZATION_ID_OPTIONS_TITLE_BAR_FORMAT_NONE_COMBOBOXITEM,
	"Everything non disponibile", // LOCALIZATION_ID_EVERYTHING_NOT_AVAILABLE_MESSAGE,
	"Aggiungi ricerca Everything", // LOCALIZATION_ID_EVERYTHING_ADD_EVERYTHING_SEARCH_CAPTION,
	"Carica ricerca Everything", // LOCALIZATION_ID_EVERYTHING_LOAD_EVERYTHING_SEARCH_CAPTION,
	"Casuale", // LOCALIZATION_ID_RANDOMIZE,
	"Copia in", // LOCALIZATION_ID_COPY_TO_CAPTION,
	"Sposta in", // LOCALIZATION_ID_MOVE_TO_CAPTION,

	// Association descriptions
	"Immagine bitmap",
	"Immagine GIF animata",
	"Immagine HEIC",
	"Immagine HEIF",
	"File icona",
	"Immagine JPEG",
	"Immagine JPEG",
	"Immagine PNG",
	"Immagine TIFF",
	"Immagine TIFF",
	"Immagine WebP",
};
