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
// Français localization
// Save as UTF-8 with BOM (required for MSVC to parse non-ASCII correctly).

const utf8_t *_localization_string_array_fr[LOCALIZATION_ID_COUNT] = 
{
	// Application name
	"Français", // LOCALIZATION_ID_LANGUAGE

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
	"&Fichier", // LOCALIZATION_ID_FILE,
	"&Ouvrir un fichier...", // LOCALIZATION_ID_OPEN_FILE,
	"Ouvrir un &dossier...", // LOCALIZATION_ID_OPEN_FOLDER,
	"Ouvrir la &recherche Everything...", // LOCALIZATION_ID_OPEN_EVERYTHING_SEARCH,
	"&Ajouter un fichier...", // LOCALIZATION_ID_ADD_FILE,
	"Ajouter un dossier...", // LOCALIZATION_ID_ADD_FOLDER,
	"Ajouter une recherche Everything...", // LOCALIZATION_ID_ADD_EVERYTHING_SEARCH,
	"Ouvrir l'&emplacement du fichier...", // LOCALIZATION_ID_OPEN_FILE_LOCATION,
	"&Modifier...", // LOCALIZATION_ID_EDIT,
	"A&perçu...", // LOCALIZATION_ID_PREVIEW,
	"&Imprimer...", // LOCALIZATION_ID_PRINT,
	"Définir le &fond d'écran", // LOCALIZATION_ID_SET_DESKTOP_WALLPAPER,
	"&Fermer", // LOCALIZATION_ID_CLOSE,
	"&Supprimer", // LOCALIZATION_ID_DELETE,
	"Supprimer (Corbeille)", // LOCALIZATION_ID_DELETE_RECYCLE,
	"Supprimer (Définitivement)", // LOCALIZATION_ID_DELETE_PERMANENTLY,
	"Re&nommer", // LOCALIZATION_ID_RENAME,
	"&Propriétés", // LOCALIZATION_ID_PROPERTIES,
	"&Quitter", // LOCALIZATION_ID_EXIT,
	
	// Edit menu
	"&Modifier", // LOCALIZATION_ID_EDIT_MENU,
	"Co&uper", // LOCALIZATION_ID_CUT,
	"&Copier", // LOCALIZATION_ID_COPY,
	"Copier le nom du fichier", // LOCALIZATION_ID_COPY_FILENAME,
	"Copier l'&image", // LOCALIZATION_ID_COPY_IMAGE,
	"&Coller", // LOCALIZATION_ID_PASTE,
	"Pivoter dans le sens des aiguilles d'une &montre", // LOCALIZATION_ID_ROTATE_CLOCKWISE,
	"Pivoter dans le sens &inverse des aiguilles", // LOCALIZATION_ID_ROTATE_COUNTERCLOCKWISE,
	"Copier vers le &dossier...", // LOCALIZATION_ID_COPY_TO,
	"Dé&placer vers le dossier...", // LOCALIZATION_ID_MOVE_TO,
	
	// View menu
	"&Affichage", // LOCALIZATION_ID_VIEW,
	"Légende", // LOCALIZATION_ID_CAPTION,
	"Cadre", // LOCALIZATION_ID_FRAME,
	"&Menu", // LOCALIZATION_ID_MENU,
	"&Barre d'état", // LOCALIZATION_ID_STATUS_BAR,
	"&Contrôles", // LOCALIZATION_ID_CONTROLS,
	"&Préréglage", // LOCALIZATION_ID_PRESET,
	"&Minimal", // LOCALIZATION_ID_MINIMAL,
	"&Compact", // LOCALIZATION_ID_COMPACT,
	"&Normal", // LOCALIZATION_ID_NORMAL,
	"P&lein écran", // LOCALIZATION_ID_FULLSCREEN,
	"&Diaporama", // LOCALIZATION_ID_SLIDESHOW,
	"&Taille de la fenêtre", // LOCALIZATION_ID_VIEW_WINDOW_SIZE,
	"50%", // LOCALIZATION_ID_VIEW_WINDOW_SIZE_50_PERCENT,
	"100%", // LOCALIZATION_ID_VIEW_WINDOW_SIZE_100_PERCENT,
	"200%", // LOCALIZATION_ID_VIEW_WINDOW_SIZE_200_PERCENT,
	"&Ajustement automatique", // LOCALIZATION_ID_VIEW_WINDOW_SIZE_AUTO_FIT,
	"&Actualiser", // LOCALIZATION_ID_REFRESH,
	"&Autoriser la réduction", // LOCALIZATION_ID_ALLOW_SHRINKING,
	"&Conserver le ratio", // LOCALIZATION_ID_KEEP_ASPECT_RATIO,
	"&Remplir la fenêtre", // LOCALIZATION_ID_FILL_WINDOW,
	"1:1", // LOCALIZATION_ID_ONE_TO_ONE,
	"&Meilleur ajustement", // LOCALIZATION_ID_BEST_FIT,
	"Pa&noramique && balayage", // LOCALIZATION_ID_PAN_SCAN,
	"&Augmenter la taille", // LOCALIZATION_ID_INCREASE_SIZE,
	"&Diminuer la taille", // LOCALIZATION_ID_DECREASE_SIZE,
	"Augme&nter la largeur", // LOCALIZATION_ID_INCREASE_WIDTH,
	"Di&minuer la largeur", // LOCALIZATION_ID_DECREASE_WIDTH,
	"Augmenter la &hauteur", // LOCALIZATION_ID_INCREASE_HEIGHT,
	"Diminuer la &hauteur", // LOCALIZATION_ID_DECREASE_HEIGHT,
	"&Zoom", // LOCALIZATION_ID_ZOOM,
	"Zoom &avant", // LOCALIZATION_ID_ZOOM_IN,
	"Zoom &arrière", // LOCALIZATION_ID_ZOOM_OUT,
	"&Réinitialiser", // LOCALIZATION_ID_RESET,
	"Déplacer vers le &haut", // LOCALIZATION_ID_MOVE_UP,
	"Déplacer vers le &bas", // LOCALIZATION_ID_MOVE_DOWN,
	"Déplacer vers la &gauche", // LOCALIZATION_ID_MOVE_LEFT,
	"Déplacer vers la &droite", // LOCALIZATION_ID_MOVE_RIGHT,
	"Déplacer en haut à gauche", // LOCALIZATION_ID_MOVE_UP_LEFT,
	"Déplacer en haut à droite", // LOCALIZATION_ID_MOVE_UP_RIGHT,
	"Déplacer en bas à gauche", // LOCALIZATION_ID_MOVE_DOWN_LEFT,
	"Déplacer en bas à droite", // LOCALIZATION_ID_MOVE_DOWN_RIGHT,
	"Déplacer au &centre", // LOCALIZATION_ID_MOVE_CENTER,
	"Ré&initialiser", // LOCALIZATION_ID_PANSCAN_RESET,
	"Toujours au &premier plan", // LOCALIZATION_ID_ON_TOP,
	"&Toujours", // LOCALIZATION_ID_ALWAYS,
	"&Pendant le diaporama ou l'animation", // LOCALIZATION_ID_WHILE_PLAYING_OR_ANIMATING,
	"&Jamais", // LOCALIZATION_ID_NEVER,
	"&Options", // LOCALIZATION_ID_OPTIONS,
	"&Transition", // LOCALIZATION_ID_TRANSITION,
	"&Aucune", // LOCALIZATION_ID_TRANSITION_NONE,
	"&Fondu", // LOCALIZATION_ID_TRANSITION_FADE,
	"Durée...", // LOCALIZATION_ID_TRANSITION_DURATION,
	
	// Slideshow menu
	"&Diaporama", // LOCALIZATION_ID_SLIDESHOW_MENU,
	"&Lecture/Pause", // LOCALIZATION_ID_PLAY_PAUSE,
	"&Vitesse", // LOCALIZATION_ID_RATE,
	"&Diminuer la vitesse", // LOCALIZATION_ID_DECREASE_RATE,
	"&Augmenter la vitesse", // LOCALIZATION_ID_INCREASE_RATE,
	"250 millisecondes", // LOCALIZATION_ID_RATE_250_MILLISECONDS,
	"500 millisecondes", // LOCALIZATION_ID_RATE_500_MILLISECONDS,
	"&1 seconde", // LOCALIZATION_ID_RATE_1_SECOND,
	"&2 secondes", // LOCALIZATION_ID_RATE_2_SECONDS,
	"&3 secondes", // LOCALIZATION_ID_RATE_3_SECONDS,
	"&4 secondes", // LOCALIZATION_ID_RATE_4_SECONDS,
	"&5 secondes", // LOCALIZATION_ID_RATE_5_SECONDS,
	"&6 secondes", // LOCALIZATION_ID_RATE_6_SECONDS,
	"&7 secondes", // LOCALIZATION_ID_RATE_7_SECONDS,
	"&8 secondes", // LOCALIZATION_ID_RATE_8_SECONDS,
	"&9 secondes", // LOCALIZATION_ID_RATE_9_SECONDS,
	"1&0 secondes", // LOCALIZATION_ID_RATE_10_SECONDS,
	"20 secondes", // LOCALIZATION_ID_RATE_20_SECONDS,
	"30 secondes", // LOCALIZATION_ID_RATE_30_SECONDS,
	"40 secondes", // LOCALIZATION_ID_RATE_40_SECONDS,
	"50 secondes", // LOCALIZATION_ID_RATE_50_SECONDS,
	"1 minute",	// LOCALIZATION_ID_RATE_1_MINUTE,
	"Personnalisé...", // LOCALIZATION_ID_CUSTOM,
	"&Durée de l'animation", // LOCALIZATION_ID_RATE_ANIMATION_DURATION,
	
	// Animation menu
	"&Animation", // LOCALIZATION_ID_ANIMATION,
	"&Lecture/Pause", // LOCALIZATION_ID_ANIMATION_PLAY_PAUSE,
	"Sauter en &avant", // LOCALIZATION_ID_ANIMATION_JUMP_FORWARD,
	"Sauter en &arrière", // LOCALIZATION_ID_ANIMATION_JUMP_BACKWARD,
	"Petit saut en &avant", // LOCALIZATION_ID_ANIMATION_SHORT_JUMP_FORWARD,
	"Petit saut en &arrière", // LOCALIZATION_ID_ANIMATION_SHORT_JUMP_BACKWARD,
	"Grand saut en &avant", // LOCALIZATION_ID_ANIMATION_LONG_JUMP_FORWARD,
	"Grand saut en &arrière", // LOCALIZATION_ID_ANIMATION_LONG_JUMP_BACKWARD,
	"Pas de f&rame", // LOCALIZATION_ID_ANIMATION_FRAME_STEP,
	"Frame pré&cédente", // LOCALIZATION_ID_ANIMATION_PREVIOUS_FRAME,
	"&Première frame", // LOCALIZATION_ID_ANIMATION_FIRST_FRAME,
	"&Dernière frame", // LOCALIZATION_ID_ANIMATION_LAST_FRAME,
	"&Diminuer la vitesse", // LOCALIZATION_ID_ANIMATION_DECREASE_RATE,
	"&Augmenter la vitesse", // LOCALIZATION_ID_ANIMATION_INCREASE_RATE,
	"Ré&initialiser la vitesse", // LOCALIZATION_ID_ANIMATION_RESET_RATE,
	
	// Navigate menu
	"&Naviguer", // LOCALIZATION_ID_NAVIGATE,
	"&Suivant", // LOCALIZATION_ID_NEXT,
	"&Précédent", // LOCALIZATION_ID_PREVIOUS,
	"&Début", // LOCALIZATION_ID_HOME,
	"&Fin", // LOCALIZATION_ID_END,
	"&Trier", // LOCALIZATION_ID_SORT,
	"&Nom", // LOCALIZATION_ID_SORT_NAME,
	"&Chemin complet", // LOCALIZATION_ID_SORT_FULL_PATH,
	"&Taille", // LOCALIZATION_ID_SORT_SIZE,
	"Date de &modification", // LOCALIZATION_ID_SORT_DATE_MODIFIED,
	"Date de &création", // LOCALIZATION_ID_SORT_DATE_CREATED,
	"&Croissant", // LOCALIZATION_ID_SORT_ASCENDING,
	"&Décroissant", // LOCALIZATION_ID_SORT_DESCENDING,
	"Mélanger", // LOCALIZATION_ID_SHUFFLE,
	"&Aller à...", // LOCALIZATION_ID_JUMP_TO,
	
	// Help menu
	"&Aide", // LOCALIZATION_ID_HELP,
	"&Aide", // LOCALIZATION_ID_HELP_MENU,
	"&Options de ligne de commande", // LOCALIZATION_ID_COMMAND_LINE_OPTIONS,
	"&Page d'accueil", // LOCALIZATION_ID_HOME_PAGE,
	"&Faire un don", // LOCALIZATION_ID_DONATE,
	"&À propos", // LOCALIZATION_ID_ABOUT,
	"https://www.voidtools.com/support/voidimageviewer/", // LOCALIZATION_ID_HELP_SUPPORT_URL,
	"https://www.voidtools.com/donate/", // LOCALIZATION_ID_HELP_DONATE_URL,
	"https://www.voidtools.com/", // LOCALIZATION_ID_HELP_WEBSITE_URL,

	// Toolbar
	"Image précédente", // LOCALIZATION_ID_TOOLBAR_PREVIOUS_IMAGE_BUTTON,
	"Image suivante", // LOCALIZATION_ID_TOOLBAR_NEXT_IMAGE_BUTTON,
	"Lire le diaporama", // LOCALIZATION_ID_TOOLBAR_PLAY_SLIDESHOW_BUTTON,
	"Mettre en pause le diaporama", // LOCALIZATION_ID_TOOLBAR_PAUSE_SLIDESHOW_BUTTON,
	"Meilleur ajustement", // LOCALIZATION_ID_TOOLBAR_BEST_FIT_BUTTON,
	"Taille réelle", // LOCALIZATION_ID_TOOLBAR_ACTUAL_SIZE_BUTTON,

	// Status bar
	"PRELOAD", // LOCALIZATION_ID_STATUS_BAR_PRELOAD,
	"Chargement...", // LOCALIZATION_ID_STATUS_BAR_LOADING,
	"Fichier introuvable.", // LOCALIZATION_ID_STATUS_BAR_FILE_NOT_FOUND,
	"Échec du chargement de l'image.", // LOCALIZATION_ID_STATUS_BAR_FAILED_TO_LOAD_IMAGE,
	"Diaporama en cours", // LOCALIZATION_ID_STATUS_BAR_SLIDESHOW_PLAYING,
	"Pos %0.3f %0.3f, Zoom %0.3f %0.3f, Ratio %0.3f", // LOCALIZATION_ID_STATUS_BAR_POS_ZOOM_FORMAT,
	"Vitesse d'animation %0.3f", // LOCALIZATION_ID_STATUS_BAR_ANIMATION_RATE_FORMAT,
	"Vitesse du diaporama %d %s", // LOCALIZATION_ID_STATUS_BAR_SLIDESHOW_RATE_FORMAT,
	"Vitesse du diaporama : durée de l'animation", // LOCALIZATION_ID_STATUS_BAR_ANIMATION_DURATION,
	"minutes", // LOCALIZATION_ID_STATUS_BAR_MINUTES,
	"secondes", // LOCALIZATION_ID_STATUS_BAR_SECONDS,
	"millisecondes", // LOCALIZATION_ID_STATUS_BAR_MILLISECONDS,

	// Dialog strings
	"Options - void Image Viewer", // LOCALIZATION_ID_OPTIONS_CAPTION,
	"Général", // LOCALIZATION_ID_OPTIONS_GENERAL_DIALOG,
	"Affichage", // LOCALIZATION_ID_OPTIONS_VIEW_DIALOG,
	"Contrôles", // LOCALIZATION_ID_OPTIONS_CONTROLS_DIALOG,
	"OK", // LOCALIZATION_ID_OK_BUTTON,
	"Annuler", // LOCALIZATION_ID_CANCEL_BUTTON,
	"&Enregistrer les paramètres dans %APPDATA%\\voidImageViewer", // LOCALIZATION_ID_STORE_SETTINGS_APPDATA,
	"Autoriser plusieurs &instances", // LOCALIZATION_ID_ALLOW_MULTIPLE_INSTANCES,
	"Raccourcis du &menu Démarrer", // LOCALIZATION_ID_STARTMENU_SHORTCUTS,
	"Associations", // LOCALIZATION_ID_ASSOCIATIONS,
	"Cocher &tout", // LOCALIZATION_ID_CHECK_ALL,
	"&Décocher tout", // LOCALIZATION_ID_CHECK_NONE,
	"Mode de blit de &réduction :", // LOCALIZATION_ID_SHRINK_BLIT_MODE_STATIC,
	"Mode de blit d'&agrandissement :", // LOCALIZATION_ID_MAGNIFY_BLIT_MODE,
	"Au plus proche", // LOCALIZATION_ID_BLIT_MODE_NEAREST_COMBOBOXITEM,
	"Linéaire", // LOCALIZATION_ID_BLIT_MODE_LINEAR_COMBOBOXITEM,
	"&Taille automatique de la fenêtre :", // LOCALIZATION_ID_OPTIONS_VIEW_AUTO_SIZE_WINDOW_STATIC,
	"50%", // LOCALIZATION_ID_OPTIONS_VIEW_AUTO_SIZE_WINDOW_50_PERCENT_COMBOBOXITEM,
	"100%", // LOCALIZATION_ID_OPTIONS_VIEW_AUTO_SIZE_WINDOW_100_PERCENT_COMBOBOXITEM,
	"200%", // LOCALIZATION_ID_OPTIONS_VIEW_AUTO_SIZE_WINDOW_200_PERCENT_COMBOBOXITEM,
	"Ajustement automatique", // LOCALIZATION_ID_OPTIONS_VIEW_AUTO_SIZE_WINDOW_AUTO_FIT_COMBOBOXITEM,
	"&Jouer les animations au moins une fois dans le diaporama", // LOCALIZATION_ID_PLAY_ANIMATIONS_ONCE_STATIC,
	"Précharger l'image &suivante", // LOCALIZATION_ID_PRELOAD_NEXT_IMAGE_STATIC,
	"Mettre en cache la &dernière image", // LOCALIZATION_ID_CACHE_LAST_IMAGE_STATIC,
	"Couleur de fond en &fenêtré :", // LOCALIZATION_ID_WINDOWED_BACKGROUND_COLOR_STATIC,
	"Couleur de fond en &plein écran :", // LOCALIZATION_ID_FULLSCREEN_BACKGROUND_COLOR_STATIC,
	"Action du clic &gauche :", // LOCALIZATION_ID_LEFT_CLICK_ACTION_STATIC,
	"Action du clic &droit :", // LOCALIZATION_ID_RIGHT_CLICK_ACTION_STATIC,
	"Action de la &molette :", // LOCALIZATION_ID_MOUSE_WHEEL_ACTION_STATIC,
	"&Commandes :", // LOCALIZATION_ID_COMMANDS_STATIC,
	"Paramètres de la commande sélectionnée", // LOCALIZATION_ID_SETTINGS_FOR_SELECTED_COMMAND,
	"&Ajouter...", // LOCALIZATION_ID_ADD_KEY_BUTTON,
	"&Modifier...", // LOCALIZATION_ID_EDIT_KEY_BUTTON,
	"&Supprimer", // LOCALIZATION_ID_REMOVE_KEY_BUTTON,
	"Ajouter un raccourci clavier", // LOCALIZATION_ID_ADD_KEYBOARD_SHORTCUT_CAPTION,
	"Modifier le raccourci clavier", // LOCALIZATION_ID_EDIT_KEYBOARD_SHORTCUT_CAPTION,
	"&Touche du raccourci :", // LOCALIZATION_ID_SHORTCUT_KEY,
	"Touche de raccourci actuellement utilisée par :", // LOCALIZATION_ID_SHORTCUT_KEY_CURRENTLY_USED_BY,
	"Définir une vitesse personnalisée", // LOCALIZATION_ID_SET_CUSTOM_RATE_CAPTION,
	"&Vitesse personnalisée :", // LOCALIZATION_ID_CUSTOM_RATE_STATIC,
	"minutes", // LOCALIZATION_ID_CUSTOM_RATE_MINUTES,
	"secondes", // LOCALIZATION_ID_CUSTOM_RATE_SECONDS,
	"millisecondes", // LOCALIZATION_ID_CUSTOM_RATE_MILLISECONDS,
	"À propos de void Image Viewer", // LOCALIZATION_ID_ABOUT_CAPTION,
	"Renommer", // LOCALIZATION_ID_RENAME_CAPTION,
	"Aller à", // LOCALIZATION_ID_JUMP_TO_TITLE,
	"Copyright © %d voidtools", // LOCALIZATION_ID_ABOUT_COPYRIGHT_FORMAT,
	"support@voidtools.com", // LOCALIZATION_ID_ABOUT_EMAIL,
	"www.voidtools.com", // LOCALIZATION_ID_ABOUT_WEBSITE,
	"Ouvrir l'image", // LOCALIZATION_ID_OPEN_IMAGE_CAPTION,
	"Tous les fichiers image", // LOCALIZATION_ID_OPEN_ALL_IMAGE_FILES,
	"Tous les fichiers", // LOCALIZATION_ID_OPEN_ALL_FILES,
	"Défiler", // LOCALIZATION_ID_OPTIONS_ACTION_SCROLL_COMBOBOXITEM,
	"Lecture/Pause du diaporama", // LOCALIZATION_ID_OPTIONS_ACTION_PLAY_PAUSE_SLIDESHOW_COMBOBOXITEM,
	"Lecture/Pause de l'animation", // LOCALIZATION_ID_OPTIONS_ACTION_PLAY_PAUSE_ANIMATION_COMBOBOXITEM,
	"Zoom avant", // LOCALIZATION_ID_OPTIONS_ACTION_ZOOM_IN_COMBOBOXITEM,
	"Image suivante", // LOCALIZATION_ID_OPTIONS_ACTION_NEXT_IMAGE_COMBOBOXITEM,
	"Défilement 1:1", // LOCALIZATION_ID_OPTIONS_ACTION_ONE_TO_ONE_SCROLL_COMBOBOXITEM,
	"Défiler/Déplacer la fenêtre", // LOCALIZATION_ID_OPTIONS_ACTION_SCROLL_MOVE_WINDOW_COMBOBOXITEM,
	"Menu contextuel", // LOCALIZATION_ID_OPTIONS_ACTION_CONTEXT_MENU_COMBOBOXITEM,
	"Zoom arrière", // LOCALIZATION_ID_OPTIONS_ACTION_ZOOM_OUT_COMBOBOXITEM,
	"Image précédente", // LOCALIZATION_ID_OPTIONS_ACTION_PREVIOUS_IMAGE_COMBOBOXITEM,
	"Zoom", // LOCALIZATION_ID_OPTIONS_ACTION_ZOOM_COMBOBOXITEM,
	"Suivant/Précédent", // LOCALIZATION_ID_OPTIONS_ACTION_NEXT_PREV_COMBOBOXITEM,
	"Précédent/Suivant", // LOCALIZATION_ID_OPTIONS_ACTION_PREV_NEXT_COMBOBOXITEM,
	"&Format de la barre de titre :", // LOCALIZATION_ID_OPTIONS_TITLE_BAR_FORMAT_STATIC,
	"Chemin complet", // LOCALIZATION_ID_OPTIONS_TITLE_BAR_FORMAT_FULL_PATH_COMBOBOXITEM,
	"Nom du fichier uniquement", // LOCALIZATION_ID_OPTIONS_TITLE_BAR_FORMAT_FILENAME_ONLY_COMBOBOXITEM,
	"Aucun", // LOCALIZATION_ID_OPTIONS_TITLE_BAR_FORMAT_NONE_COMBOBOXITEM,
	"Everything n'est pas disponible", // LOCALIZATION_ID_EVERYTHING_NOT_AVAILABLE_MESSAGE,
	"Ajouter une recherche Everything", // LOCALIZATION_ID_EVERYTHING_ADD_EVERYTHING_SEARCH_CAPTION,
	"Charger une recherche Everything", // LOCALIZATION_ID_EVERYTHING_LOAD_EVERYTHING_SEARCH_CAPTION,
	"Aléatoire", // LOCALIZATION_ID_RANDOMIZE,
	"Copier vers", // LOCALIZATION_ID_COPY_TO_CAPTION,
	"Déplacer vers", // LOCALIZATION_ID_MOVE_TO_CAPTION,

	// Association descriptions
	"Image bitmap",
	"Image GIF animée",
	"Image HEIC",
	"Image HEIF",
	"Fichier d'icône",
	"Image JPEG",
	"Image JPEG",
	"Image PNG",
	"Image TIFF",
	"Image TIFF",
	"Image WebP",
	// LOCALIZATION_ID_ABOUT_PROJECT / LOCALIZATION_ID_ABOUT_PROJECT_URL
	"Page du projet",
	"https://github.com/HaiSeaman/voidImageViewer-i18n",

};
