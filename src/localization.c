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
// Language/Localization support implementation

#include "viv.h"

static const utf8_t **_localization_language_array[LOCALIZATION_LANGUAGE_COUNT] = 
{
	_localization_string_array_en_us, // LOCALIZATION_LANGUAGE_ENGLISH
	_localization_string_array_zh_cn, // LOCALIZATION_LANGUAGE_CHINESE_SIMPLIFIED
	_localization_string_array_ja,    // LOCALIZATION_LANGUAGE_JAPANESE
	_localization_string_array_ko,    // LOCALIZATION_LANGUAGE_KOREAN
	_localization_string_array_fr,    // LOCALIZATION_LANGUAGE_FRENCH
	_localization_string_array_de,    // LOCALIZATION_LANGUAGE_GERMAN
	_localization_string_array_es,    // LOCALIZATION_LANGUAGE_SPANISH
	_localization_string_array_pt,    // LOCALIZATION_LANGUAGE_PORTUGUESE
	_localization_string_array_it,    // LOCALIZATION_LANGUAGE_ITALIAN
	_localization_string_array_ar,    // LOCALIZATION_LANGUAGE_ARABIC
};

BYTE localization_language = LOCALIZATION_LANGUAGE_CHINESE_SIMPLIFIED;

const utf8_t *localization_get_string(localization_id_t localization_id)
{
#ifdef _DEBUG

if ((localization_id < 0) || (localization_id >= LOCALIZATION_ID_COUNT))
{
	debug_fatal("bad localization id %d\n",localization_id);
}

#endif
	
	return _localization_language_array[localization_language][localization_id];
}

const utf8_t *localization_get_en_us_string(localization_id_t localization_id)
{
	return _localization_string_array_en_us[localization_id];
}

void localization_set_language(localization_id_t lang)
{
	if (lang >= 0 && lang < LOCALIZATION_LANGUAGE_COUNT)
	{
		localization_language = (BYTE)lang;
		config_language = (int)lang;
		config_save_settings(config_appdata);
	}
}

int localization_is_rtl(void)
{
	return (localization_language == LOCALIZATION_LANGUAGE_ARABIC);
}

void localization_init(void)
{
	// 1. Check if user configured a valid language preference in config
	if (config_language >= 0 && config_language < LOCALIZATION_LANGUAGE_COUNT)
	{
		localization_language = (BYTE)config_language;
		return;
	}

	// Default fallback is English
	localization_language = LOCALIZATION_LANGUAGE_ENGLISH;

	// 2. Detect system language
	if (os_GetUserDefaultUILanguage)
	{
		LANGID langid;
		WORD primary_lang;
	
		langid = os_GetUserDefaultUILanguage();
		primary_lang = PRIMARYLANGID(langid);

		switch (primary_lang)
		{
			case 0x04: // LANG_CHINESE
				localization_language = LOCALIZATION_LANGUAGE_CHINESE_SIMPLIFIED;
				break;
			case 0x11: // LANG_JAPANESE
				localization_language = LOCALIZATION_LANGUAGE_JAPANESE;
				break;
			case 0x12: // LANG_KOREAN
				localization_language = LOCALIZATION_LANGUAGE_KOREAN;
				break;
			case 0x0c: // LANG_FRENCH
				localization_language = LOCALIZATION_LANGUAGE_FRENCH;
				break;
			case 0x07: // LANG_GERMAN
				localization_language = LOCALIZATION_LANGUAGE_GERMAN;
				break;
			case 0x0a: // LANG_SPANISH
				localization_language = LOCALIZATION_LANGUAGE_SPANISH;
				break;
			case 0x16: // LANG_PORTUGUESE
				localization_language = LOCALIZATION_LANGUAGE_PORTUGUESE;
				break;
			case 0x10: // LANG_ITALIAN
				localization_language = LOCALIZATION_LANGUAGE_ITALIAN;
				break;
			case 0x01: // LANG_ARABIC
				localization_language = LOCALIZATION_LANGUAGE_ARABIC;
				break;
			default:
				localization_language = LOCALIZATION_LANGUAGE_ENGLISH;
				break;
		}
	}
}
