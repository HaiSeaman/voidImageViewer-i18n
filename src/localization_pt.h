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
// Português localization
// Save as UTF-8 with BOM (required for MSVC to parse non-ASCII correctly).

static const utf8_t *_localization_string_array_pt[LOCALIZATION_ID_COUNT] = 
{
	// Application name
	"Português", // LOCALIZATION_ID_LANGUAGE

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
	"&Arquivo", // LOCALIZATION_ID_FILE,
	"&Abrir arquivo...", // LOCALIZATION_ID_OPEN_FILE,
	"Abrir &pasta...", // LOCALIZATION_ID_OPEN_FOLDER,
	"Abrir &pesquisa do Everything...", // LOCALIZATION_ID_OPEN_EVERYTHING_SEARCH,
	"&Adicionar arquivo...", // LOCALIZATION_ID_ADD_FILE,
	"Adicionar pasta...", // LOCALIZATION_ID_ADD_FOLDER,
	"Adicionar pesquisa do Everything...", // LOCALIZATION_ID_ADD_EVERYTHING_SEARCH,
	"Abrir &local do arquivo...", // LOCALIZATION_ID_OPEN_FILE_LOCATION,
	"&Editar...", // LOCALIZATION_ID_EDIT,
	"&Visualizar...", // LOCALIZATION_ID_PREVIEW,
	"&Imprimir...", // LOCALIZATION_ID_PRINT,
	"Definir como papel de parede do &desktop", // LOCALIZATION_ID_SET_DESKTOP_WALLPAPER,
	"&Fechar", // LOCALIZATION_ID_CLOSE,
	"&Excluir", // LOCALIZATION_ID_DELETE,
	"Excluir (Lixeira)", // LOCALIZATION_ID_DELETE_RECYCLE,
	"Excluir (Permanentemente)", // LOCALIZATION_ID_DELETE_PERMANENTLY,
	"&Renomear", // LOCALIZATION_ID_RENAME,
	"&Propriedades", // LOCALIZATION_ID_PROPERTIES,
	"&Sair", // LOCALIZATION_ID_EXIT,
	
	// Edit menu
	"&Editar", // LOCALIZATION_ID_EDIT_MENU,
	"Recor&tar", // LOCALIZATION_ID_CUT,
	"&Copiar", // LOCALIZATION_ID_COPY,
	"Copiar nome do arquivo", // LOCALIZATION_ID_COPY_FILENAME,
	"Copiar &imagem", // LOCALIZATION_ID_COPY_IMAGE,
	"&Colar", // LOCALIZATION_ID_PASTE,
	"Girar no sentido &horário", // LOCALIZATION_ID_ROTATE_CLOCKWISE,
	"Girar no sentido &anti-horário", // LOCALIZATION_ID_ROTATE_COUNTERCLOCKWISE,
	"Copiar para &pasta...", // LOCALIZATION_ID_COPY_TO,
	"&Mover para pasta...", // LOCALIZATION_ID_MOVE_TO,
	
	// View menu
	"&Exibir", // LOCALIZATION_ID_VIEW,
	"Legenda", // LOCALIZATION_ID_CAPTION,
	"Moldura", // LOCALIZATION_ID_FRAME,
	"&Menu", // LOCALIZATION_ID_MENU,
	"&Barra de status", // LOCALIZATION_ID_STATUS_BAR,
	"&Controles", // LOCALIZATION_ID_CONTROLS,
	"&Predefinição", // LOCALIZATION_ID_PRESET,
	"&Mínimo", // LOCALIZATION_ID_MINIMAL,
	"&Compacto", // LOCALIZATION_ID_COMPACT,
	"&Normal", // LOCALIZATION_ID_NORMAL,
	"&Tela cheia", // LOCALIZATION_ID_FULLSCREEN,
	"&Apresentação de slides", // LOCALIZATION_ID_SLIDESHOW,
	"&Tamanho da janela", // LOCALIZATION_ID_VIEW_WINDOW_SIZE,
	"50%", // LOCALIZATION_ID_VIEW_WINDOW_SIZE_50_PERCENT,
	"100%", // LOCALIZATION_ID_VIEW_WINDOW_SIZE_100_PERCENT,
	"200%", // LOCALIZATION_ID_VIEW_WINDOW_SIZE_200_PERCENT,
	"&Ajuste automático", // LOCALIZATION_ID_VIEW_WINDOW_SIZE_AUTO_FIT,
	"&Atualizar", // LOCALIZATION_ID_REFRESH,
	"&Permitir redução", // LOCALIZATION_ID_ALLOW_SHRINKING,
	"&Manter proporção", // LOCALIZATION_ID_KEEP_ASPECT_RATIO,
	"&Preencher janela", // LOCALIZATION_ID_FILL_WINDOW,
	"1:1", // LOCALIZATION_ID_ONE_TO_ONE,
	"&Melhor ajuste", // LOCALIZATION_ID_BEST_FIT,
	"&Panorâmica && varredura", // LOCALIZATION_ID_PAN_SCAN,
	"&Aumentar tamanho", // LOCALIZATION_ID_INCREASE_SIZE,
	"&Diminuir tamanho", // LOCALIZATION_ID_DECREASE_SIZE,
	"A&umentar largura", // LOCALIZATION_ID_INCREASE_WIDTH,
	"D&iminuir largura", // LOCALIZATION_ID_DECREASE_WIDTH,
	"Aumentar &altura", // LOCALIZATION_ID_INCREASE_HEIGHT,
	"Diminuir &altura", // LOCALIZATION_ID_DECREASE_HEIGHT,
	"&Zoom", // LOCALIZATION_ID_ZOOM,
	"Zoom &para dentro", // LOCALIZATION_ID_ZOOM_IN,
	"Zoom &para fora", // LOCALIZATION_ID_ZOOM_OUT,
	"&Redefinir", // LOCALIZATION_ID_RESET,
	"Mover para &cima", // LOCALIZATION_ID_MOVE_UP,
	"Mover para &baixo", // LOCALIZATION_ID_MOVE_DOWN,
	"Mover para a &esquerda", // LOCALIZATION_ID_MOVE_LEFT,
	"Mover para a &direita", // LOCALIZATION_ID_MOVE_RIGHT,
	"Mover para cima à esquerda", // LOCALIZATION_ID_MOVE_UP_LEFT,
	"Mover para cima à direita", // LOCALIZATION_ID_MOVE_UP_RIGHT,
	"Mover para baixo à esquerda", // LOCALIZATION_ID_MOVE_DOWN_LEFT,
	"Mover para baixo à direita", // LOCALIZATION_ID_MOVE_DOWN_RIGHT,
	"Mover para o &centro", // LOCALIZATION_ID_MOVE_CENTER,
	"Re&definir", // LOCALIZATION_ID_PANSCAN_RESET,
	"Sempre no &topo", // LOCALIZATION_ID_ON_TOP,
	"&Sempre", // LOCALIZATION_ID_ALWAYS,
	"&Durante apresentação de slides ou animação", // LOCALIZATION_ID_WHILE_PLAYING_OR_ANIMATING,
	"&Nunca", // LOCALIZATION_ID_NEVER,
	"&Opções...", // LOCALIZATION_ID_OPTIONS,
	"&Transição", // LOCALIZATION_ID_TRANSITION,
	"&Nenhuma", // LOCALIZATION_ID_TRANSITION_NONE,
	"&Desvanecer", // LOCALIZATION_ID_TRANSITION_FADE,
	"Duração...", // LOCALIZATION_ID_TRANSITION_DURATION,
	"Definir duração da transição", // LOCALIZATION_ID_SET_TRANSITION_DURATION_CAPTION,
	"&Duração (ms):", // LOCALIZATION_ID_TRANSITION_DURATION_STATIC,
	"&Mostrar interface ao passar o mouse", // LOCALIZATION_ID_HOVER_SHOW_UI,
	
	// Slideshow menu
	"&Apresentação de slides", // LOCALIZATION_ID_SLIDESHOW_MENU,
	"&Reproduzir/Pausar", // LOCALIZATION_ID_PLAY_PAUSE,
	"&Velocidade", // LOCALIZATION_ID_RATE,
	"&Diminuir velocidade", // LOCALIZATION_ID_DECREASE_RATE,
	"&Aumentar velocidade", // LOCALIZATION_ID_INCREASE_RATE,
	"250 milissegundos", // LOCALIZATION_ID_RATE_250_MILLISECONDS,
	"500 milissegundos", // LOCALIZATION_ID_RATE_500_MILLISECONDS,
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
	"&Duração da animação", // LOCALIZATION_ID_RATE_ANIMATION_DURATION,
	
	// Animation menu
	"&Animação", // LOCALIZATION_ID_ANIMATION,
	"&Reproduzir/Pausar", // LOCALIZATION_ID_ANIMATION_PLAY_PAUSE,
	"Pular &para frente", // LOCALIZATION_ID_ANIMATION_JUMP_FORWARD,
	"Pular &para trás", // LOCALIZATION_ID_ANIMATION_JUMP_BACKWARD,
	"Pulo curto &para frente", // LOCALIZATION_ID_ANIMATION_SHORT_JUMP_FORWARD,
	"Pulo curto &para trás", // LOCALIZATION_ID_ANIMATION_SHORT_JUMP_BACKWARD,
	"Pulo longo &para frente", // LOCALIZATION_ID_ANIMATION_LONG_JUMP_FORWARD,
	"Pulo longo &para trás", // LOCALIZATION_ID_ANIMATION_LONG_JUMP_BACKWARD,
	"&Passo de quadro", // LOCALIZATION_ID_ANIMATION_FRAME_STEP,
	"Quadro &anterior", // LOCALIZATION_ID_ANIMATION_PREVIOUS_FRAME,
	"&Primeiro quadro", // LOCALIZATION_ID_ANIMATION_FIRST_FRAME,
	"&Último quadro", // LOCALIZATION_ID_ANIMATION_LAST_FRAME,
	"&Diminuir velocidade", // LOCALIZATION_ID_ANIMATION_DECREASE_RATE,
	"&Aumentar velocidade", // LOCALIZATION_ID_ANIMATION_INCREASE_RATE,
	"&Redefinir velocidade", // LOCALIZATION_ID_ANIMATION_RESET_RATE,
	
	// Navigate menu
	"&Navegar", // LOCALIZATION_ID_NAVIGATE,
	"&Próximo", // LOCALIZATION_ID_NEXT,
	"&Anterior", // LOCALIZATION_ID_PREVIOUS,
	"&Início", // LOCALIZATION_ID_HOME,
	"&Fim", // LOCALIZATION_ID_END,
	"&Ordenar", // LOCALIZATION_ID_SORT,
	"&Nome", // LOCALIZATION_ID_SORT_NAME,
	"&Caminho completo", // LOCALIZATION_ID_SORT_FULL_PATH,
	"&Tamanho", // LOCALIZATION_ID_SORT_SIZE,
	"Data de &modificação", // LOCALIZATION_ID_SORT_DATE_MODIFIED,
	"Data de &criação", // LOCALIZATION_ID_SORT_DATE_CREATED,
	"&Crescente", // LOCALIZATION_ID_SORT_ASCENDING,
	"&Decrescente", // LOCALIZATION_ID_SORT_DESCENDING,
	"Embaralhar", // LOCALIZATION_ID_SHUFFLE,
	"&Ir para...", // LOCALIZATION_ID_JUMP_TO,
	
	// Help menu
	"A&juda", // LOCALIZATION_ID_HELP,
	"A&juda", // LOCALIZATION_ID_HELP_MENU,
	"&Opções de linha de comando", // LOCALIZATION_ID_COMMAND_LINE_OPTIONS,
	"&Página inicial", // LOCALIZATION_ID_HOME_PAGE,
	"&Doar", // LOCALIZATION_ID_DONATE,
	"&Sobre", // LOCALIZATION_ID_ABOUT,
	"https://www.voidtools.com/support/voidimageviewer/", // LOCALIZATION_ID_HELP_SUPPORT_URL,
	"https://www.voidtools.com/donate/", // LOCALIZATION_ID_HELP_DONATE_URL,
	"https://www.voidtools.com/", // LOCALIZATION_ID_HELP_WEBSITE_URL,

	// Toolbar
	"Imagem anterior", // LOCALIZATION_ID_TOOLBAR_PREVIOUS_IMAGE_BUTTON,
	"Próxima imagem", // LOCALIZATION_ID_TOOLBAR_NEXT_IMAGE_BUTTON,
	"Reproduzir apresentação de slides", // LOCALIZATION_ID_TOOLBAR_PLAY_SLIDESHOW_BUTTON,
	"Pausar apresentação de slides", // LOCALIZATION_ID_TOOLBAR_PAUSE_SLIDESHOW_BUTTON,
	"Melhor ajuste", // LOCALIZATION_ID_TOOLBAR_BEST_FIT_BUTTON,
	"Tamanho real", // LOCALIZATION_ID_TOOLBAR_ACTUAL_SIZE_BUTTON,

	// Status bar
	"PRELOAD", // LOCALIZATION_ID_STATUS_BAR_PRELOAD,
	"Carregando...", // LOCALIZATION_ID_STATUS_BAR_LOADING,
	"Arquivo não encontrado.", // LOCALIZATION_ID_STATUS_BAR_FILE_NOT_FOUND,
	"Falha ao carregar a imagem.", // LOCALIZATION_ID_STATUS_BAR_FAILED_TO_LOAD_IMAGE,
	"Apresentação de slides em reprodução", // LOCALIZATION_ID_STATUS_BAR_SLIDESHOW_PLAYING,
	"Pos %0.3f %0.3f, Zoom %0.3f %0.3f, Proporção %0.3f", // LOCALIZATION_ID_STATUS_BAR_POS_ZOOM_FORMAT,
	"Velocidade da animação %0.3f", // LOCALIZATION_ID_STATUS_BAR_ANIMATION_RATE_FORMAT,
	"Velocidade da apresentação %d %s", // LOCALIZATION_ID_STATUS_BAR_SLIDESHOW_RATE_FORMAT,
	"Velocidade da apresentação: duração da animação", // LOCALIZATION_ID_STATUS_BAR_ANIMATION_DURATION,
	"minutos", // LOCALIZATION_ID_STATUS_BAR_MINUTES,
	"segundos", // LOCALIZATION_ID_STATUS_BAR_SECONDS,
	"milissegundos", // LOCALIZATION_ID_STATUS_BAR_MILLISECONDS,

	// Dialog strings
	"Opções - void Image Viewer", // LOCALIZATION_ID_OPTIONS_CAPTION,
	"Geral", // LOCALIZATION_ID_OPTIONS_GENERAL_DIALOG,
	"Exibir", // LOCALIZATION_ID_OPTIONS_VIEW_DIALOG,
	"Controles", // LOCALIZATION_ID_OPTIONS_CONTROLS_DIALOG,
	"OK", // LOCALIZATION_ID_OK_BUTTON,
	"Cancelar", // LOCALIZATION_ID_CANCEL_BUTTON,
	"&Salvar configurações em %APPDATA%\\voidImageViewer", // LOCALIZATION_ID_STORE_SETTINGS_APPDATA,
	"Permitir várias &instâncias", // LOCALIZATION_ID_ALLOW_MULTIPLE_INSTANCES,
	"Atalhos do &menu Iniciar", // LOCALIZATION_ID_STARTMENU_SHORTCUTS,
	"Associações", // LOCALIZATION_ID_ASSOCIATIONS,
	"Marcar &tudo", // LOCALIZATION_ID_CHECK_ALL,
	"Desmarcar &tudo", // LOCALIZATION_ID_CHECK_NONE,
	"Modo de blit de &redução:", // LOCALIZATION_ID_SHRINK_BLIT_MODE_STATIC,
	"Modo de blit de &ampliação:", // LOCALIZATION_ID_MAGNIFY_BLIT_MODE,
	"Mais próximo", // LOCALIZATION_ID_BLIT_MODE_NEAREST_COMBOBOXITEM,
	"Linear", // LOCALIZATION_ID_BLIT_MODE_LINEAR_COMBOBOXITEM,
	"&Tamanho automático da janela:", // LOCALIZATION_ID_OPTIONS_VIEW_AUTO_SIZE_WINDOW_STATIC,
	"50%", // LOCALIZATION_ID_OPTIONS_VIEW_AUTO_SIZE_WINDOW_50_PERCENT_COMBOBOXITEM,
	"100%", // LOCALIZATION_ID_OPTIONS_VIEW_AUTO_SIZE_WINDOW_100_PERCENT_COMBOBOXITEM,
	"200%", // LOCALIZATION_ID_OPTIONS_VIEW_AUTO_SIZE_WINDOW_200_PERCENT_COMBOBOXITEM,
	"Ajuste automático", // LOCALIZATION_ID_OPTIONS_VIEW_AUTO_SIZE_WINDOW_AUTO_FIT_COMBOBOXITEM,
	"&Reproduzir animações pelo menos uma vez na apresentação", // LOCALIZATION_ID_PLAY_ANIMATIONS_ONCE_STATIC,
	"Pré-carregar &próxima imagem", // LOCALIZATION_ID_PRELOAD_NEXT_IMAGE_STATIC,
	"Armazenar em cache a &última imagem", // LOCALIZATION_ID_CACHE_LAST_IMAGE_STATIC,
	"Cor de fundo em &janela:", // LOCALIZATION_ID_WINDOWED_BACKGROUND_COLOR_STATIC,
	"Cor de fundo em &tela cheia:", // LOCALIZATION_ID_FULLSCREEN_BACKGROUND_COLOR_STATIC,
	"Ação do clique &esquerdo:", // LOCALIZATION_ID_LEFT_CLICK_ACTION_STATIC,
	"Ação do clique &direito:", // LOCALIZATION_ID_RIGHT_CLICK_ACTION_STATIC,
	"Ação da &roda do mouse:", // LOCALIZATION_ID_MOUSE_WHEEL_ACTION_STATIC,
	"&Comandos:", // LOCALIZATION_ID_COMMANDS_STATIC,
	"Configurações do comando selecionado", // LOCALIZATION_ID_SETTINGS_FOR_SELECTED_COMMAND,
	"&Adicionar...", // LOCALIZATION_ID_ADD_KEY_BUTTON,
	"&Editar...", // LOCALIZATION_ID_EDIT_KEY_BUTTON,
	"&Remover", // LOCALIZATION_ID_REMOVE_KEY_BUTTON,
	"Adicionar atalho de teclado", // LOCALIZATION_ID_ADD_KEYBOARD_SHORTCUT_CAPTION,
	"Editar atalho de teclado", // LOCALIZATION_ID_EDIT_KEYBOARD_SHORTCUT_CAPTION,
	"&Tecla de atalho:", // LOCALIZATION_ID_SHORTCUT_KEY,
	"Tecla de atalho atualmente usada por:", // LOCALIZATION_ID_SHORTCUT_KEY_CURRENTLY_USED_BY,
	"&Remover", // LOCALIZATION_ID_REMOVE,
	"Definir velocidade personalizada", // LOCALIZATION_ID_SET_CUSTOM_RATE_CAPTION,
	"&Velocidade personalizada:", // LOCALIZATION_ID_CUSTOM_RATE_STATIC,
	"minutos", // LOCALIZATION_ID_CUSTOM_RATE_MINUTES,
	"segundos", // LOCALIZATION_ID_CUSTOM_RATE_SECONDS,
	"milissegundos", // LOCALIZATION_ID_CUSTOM_RATE_MILLISECONDS,
	"Sobre void Image Viewer", // LOCALIZATION_ID_ABOUT_CAPTION,
	"Renomear", // LOCALIZATION_ID_RENAME_CAPTION,
	"Ir para", // LOCALIZATION_ID_JUMP_TO_TITLE,
	"Pesquisar no Everything", // LOCALIZATION_ID_SEARCH_EVERYTHING,
	"Copyright © %d voidtools", // LOCALIZATION_ID_ABOUT_COPYRIGHT_FORMAT,
	"support@voidtools.com", // LOCALIZATION_ID_ABOUT_EMAIL,
	"www.voidtools.com", // LOCALIZATION_ID_ABOUT_WEBSITE,
	"Abrir imagem", // LOCALIZATION_ID_OPEN_IMAGE_CAPTION,
	"Todos os arquivos de imagem", // LOCALIZATION_ID_OPEN_ALL_IMAGE_FILES,
	"Todos os arquivos", // LOCALIZATION_ID_OPEN_ALL_FILES,
	"Rolar", // LOCALIZATION_ID_OPTIONS_ACTION_SCROLL_COMBOBOXITEM,
	"Reproduzir/Pausar apresentação", // LOCALIZATION_ID_OPTIONS_ACTION_PLAY_PAUSE_SLIDESHOW_COMBOBOXITEM,
	"Reproduzir/Pausar animação", // LOCALIZATION_ID_OPTIONS_ACTION_PLAY_PAUSE_ANIMATION_COMBOBOXITEM,
	"Zoom para dentro", // LOCALIZATION_ID_OPTIONS_ACTION_ZOOM_IN_COMBOBOXITEM,
	"Próxima imagem", // LOCALIZATION_ID_OPTIONS_ACTION_NEXT_IMAGE_COMBOBOXITEM,
	"Rolagem 1:1", // LOCALIZATION_ID_OPTIONS_ACTION_ONE_TO_ONE_SCROLL_COMBOBOXITEM,
	"Rolar/Mover janela", // LOCALIZATION_ID_OPTIONS_ACTION_SCROLL_MOVE_WINDOW_COMBOBOXITEM,
	"Menu de contexto", // LOCALIZATION_ID_OPTIONS_ACTION_CONTEXT_MENU_COMBOBOXITEM,
	"Zoom para fora", // LOCALIZATION_ID_OPTIONS_ACTION_ZOOM_OUT_COMBOBOXITEM,
	"Imagem anterior", // LOCALIZATION_ID_OPTIONS_ACTION_PREVIOUS_IMAGE_COMBOBOXITEM,
	"Zoom", // LOCALIZATION_ID_OPTIONS_ACTION_ZOOM_COMBOBOXITEM,
	"Próximo/Anterior", // LOCALIZATION_ID_OPTIONS_ACTION_NEXT_PREV_COMBOBOXITEM,
	"Anterior/Próximo", // LOCALIZATION_ID_OPTIONS_ACTION_PREV_NEXT_COMBOBOXITEM,
	"&Formato da barra de título:", // LOCALIZATION_ID_OPTIONS_TITLE_BAR_FORMAT_STATIC,
	"Caminho completo", // LOCALIZATION_ID_OPTIONS_TITLE_BAR_FORMAT_FULL_PATH_COMBOBOXITEM,
	"Somente nome do arquivo", // LOCALIZATION_ID_OPTIONS_TITLE_BAR_FORMAT_FILENAME_ONLY_COMBOBOXITEM,
	"Nenhum", // LOCALIZATION_ID_OPTIONS_TITLE_BAR_FORMAT_NONE_COMBOBOXITEM,
	"Everything não está disponível", // LOCALIZATION_ID_EVERYTHING_NOT_AVAILABLE_MESSAGE,
	"Adicionar pesquisa do Everything", // LOCALIZATION_ID_EVERYTHING_ADD_EVERYTHING_SEARCH_CAPTION,
	"Carregar pesquisa do Everything", // LOCALIZATION_ID_EVERYTHING_LOAD_EVERYTHING_SEARCH_CAPTION,
	"Aleatório", // LOCALIZATION_ID_RANDOMIZE,
	"Copiar para", // LOCALIZATION_ID_COPY_TO_CAPTION,
	"Mover para", // LOCALIZATION_ID_MOVE_TO_CAPTION,

	// Association descriptions
	"Imagem bitmap",
	"Imagem GIF animada",
	"Arquivo de ícone",
	"Imagem JPEG",
	"Imagem JPEG",
	"Imagem PNG",
	"Imagem TIFF",
	"Imagem TIFF",
	"Imagem WebP",
};
