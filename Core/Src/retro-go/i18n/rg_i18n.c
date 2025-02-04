#pragma GCC diagnostic ignored "-Wstack-usage="
#pragma GCC diagnostic ignored "-Wdiscarded-qualifiers"
#pragma GCC diagnostic ignored "-Wchar-subscripts"

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

#if !defined (INCLUDED_ZH_CN)
#define INCLUDED_ZH_CN 0
#endif
#if !defined (INCLUDED_ZH_TW)
#define INCLUDED_ZH_TW 0
#endif
#if !defined (INCLUDED_JA_JP)
#define INCLUDED_JA_JP 0
#endif
#if !defined (INCLUDED_KO_KR)
#define INCLUDED_KO_KR 0
#endif
#if !defined (INCLUDED_ES_ES)
#define INCLUDED_ES_ES 1
#endif
#if !defined (INCLUDED_PT_PT)
#define INCLUDED_PT_PT 1
#endif
#if !defined (INCLUDED_FR_FR)
#define INCLUDED_FR_FR 1
#endif
#if !defined (INCLUDED_IT_IT)
#define INCLUDED_IT_IT 1
#endif
#if !defined (INCLUDED_DE_DE)
#define INCLUDED_DE_DE 1
#endif
#if !defined (INCLUDED_DE_DE)
#define INCLUDED_DE_DE 1
#endif
#if !defined (INCLUDED_RU_RU)
#define INCLUDED_RU_RU 1
#endif


#if !defined (BIG_BANK)
#define BIG_BANK 1
#endif

#include "rg_i18n.h"
#include "rg_i18n_lang.h"
#include "gw_lcd.h"
#include "main.h"
#include "odroid_system.h"
#include "odroid_overlay.h"

#if ((BIG_BANK == 1) && (EXTFLASH_SIZE <= 16*1024*1024)) || SD_CARD == 1
#define FONT_DATA
#else
#define FONT_DATA __attribute__((section(".extflash_font")))
#endif

#if ((BIG_BANK == 1) && (EXTFLASH_SIZE <= 16*1024*1024)) || SD_CARD == 1
#define LANG_DATA
#else
#define LANG_DATA __attribute__((section(".extflash_emu_data")))
#endif

#include "fonts/font_cp1252_Serif.h"

#if !SINGLE_FONT
#include "fonts/font_cp1252_Serif_Bold.h"
#include "fonts/font_cp1252_Serif_CJK.h"
#include "fonts/font_cp1252_Sans_serif.h"
#include "fonts/font_cp1252_Sans_serif_Bold.h"
#include "fonts/font_cp1252_Greybeard.h"
#include "fonts/font_cp1252_Unbalanced.h"
#include "fonts/font_cp1252_rock12.h"
#include "fonts/font_cp1252_haeberli12.h"
#endif

#if INCLUDED_JA_JP == 1
#include "fonts/font_cp932_ja_jp.h"
#endif
#if INCLUDED_ZH_CN == 1
#include "fonts/font_cp936_zh_cn.h"
#endif
#if INCLUDED_KO_KR == 1
#include "fonts/font_cp949_ko_kr.h"
#endif
#if INCLUDED_ZH_TW == 1
#include "fonts/font_cp950_zh_tw.h"
#endif
#if INCLUDED_RU_RU == 1
#include "fonts/font_cp1251_Serif.h"
#if !SINGLE_FONT
#include "fonts/font_cp1251_Serif_Bold.h"
#include "fonts/font_cp1251_Sans_serif.h"
#include "fonts/font_cp1251_Sans_serif_Bold.h"
#include "fonts/font_cp1251_Greybeard.h"
#endif
#endif

#if SINGLE_FONT
const char *gui_fonts[9] = {
    font_cp1252_Serif, font_cp1252_Serif, font_cp1252_Serif,
    font_cp1252_Serif, font_cp1252_Serif, font_cp1252_Serif,
    font_cp1252_Serif, font_cp1252_Serif, font_cp1252_Serif,
    };
#else
const char *gui_fonts[9] = {
    font_cp1252_Serif,    font_cp1252_Serif_Bold,    font_cp1252_Serif_CJK,
    font_cp1252_Sans_serif,    font_cp1252_Sans_serif_Bold,    font_cp1252_Greybeard,
    font_cp1252_Unbalanced,    font_cp1252_rock12,    font_cp1252_haeberli12,
    };
#endif


#if INCLUDED_JA_JP == 1
const char *ja_jp_fonts[9] = {
    font_cp932_ja_jp,    font_cp932_ja_jp,    font_cp932_ja_jp,
    font_cp932_ja_jp,    font_cp932_ja_jp,    font_cp932_ja_jp,
    font_cp932_ja_jp,    font_cp932_ja_jp,    font_cp932_ja_jp,
    };
#endif
#if INCLUDED_ZH_CN == 1
const char *zh_cn_fonts[9] = {
    font_cp936_zh_cn,    font_cp936_zh_cn,    font_cp936_zh_cn,
    font_cp936_zh_cn,    font_cp936_zh_cn,    font_cp936_zh_cn,
    font_cp936_zh_cn,    font_cp936_zh_cn,    font_cp936_zh_cn,
    };
#endif
#if INCLUDED_KO_KR == 1
const char *ko_kr_fonts[9] = {
    font_cp949_ko_kr,    font_cp949_ko_kr,    font_cp949_ko_kr,
    font_cp949_ko_kr,    font_cp949_ko_kr,    font_cp949_ko_kr,
    font_cp949_ko_kr,    font_cp949_ko_kr,    font_cp949_ko_kr,
    };
#endif
#if INCLUDED_ZH_TW == 1
const char *zh_tw_fonts[9] = {
    font_cp950_zh_tw,    font_cp950_zh_tw,    font_cp950_zh_tw,
    font_cp950_zh_tw,    font_cp950_zh_tw,    font_cp950_zh_tw,
    font_cp950_zh_tw,    font_cp950_zh_tw,    font_cp950_zh_tw,
    };
#endif
#if INCLUDED_RU_RU == 1
#if SINGLE_FONT
const char *cp1251_fonts[9] = {
    font_cp1251_Serif, font_cp1251_Serif, font_cp1251_Serif,
    font_cp1251_Serif, font_cp1251_Serif, font_cp1251_Serif,
    font_cp1251_Serif, font_cp1251_Serif, font_cp1251_Serif,
    };
#else
const char *cp1251_fonts[9] = {
    font_cp1251_Serif,    font_cp1251_Serif_Bold,    font_cp1251_Serif,
    font_cp1251_Sans_serif,    font_cp1251_Sans_serif_Bold,    font_cp1251_Greybeard,
    font_cp1251_Serif_Bold,    font_cp1251_Serif_Bold,    font_cp1251_Serif_Bold,
    };
#endif
#endif


#include "rg_i18n_en_us.c"

#if INCLUDED_ES_ES == 1
#include "rg_i18n_es_es.c"
#endif

#if INCLUDED_PT_PT == 1
#include "rg_i18n_pt_pt.c"
#endif

#if INCLUDED_FR_FR == 1
#include "rg_i18n_fr_fr.c"
#endif

#if INCLUDED_IT_IT == 1
#include "rg_i18n_it_it.c"
#endif

#if INCLUDED_DE_DE == 1
#include "rg_i18n_de_de.c"
#endif

#if INCLUDED_ZH_CN == 1
#include "rg_i18n_zh_cn.c"
#endif

#if INCLUDED_ZH_TW == 1
#include "rg_i18n_zh_tw.c"
#endif

#if INCLUDED_KO_KR == 1
#include "rg_i18n_ko_kr.c"
#endif

#if INCLUDED_JA_JP == 1
#include "rg_i18n_ja_jp.c"
#endif

#if INCLUDED_RU_RU == 1
#include "rg_i18n_ru_ru.c"
#endif

static uint16_t overlay_buffer[ODROID_SCREEN_WIDTH * 12 * 2] __attribute__((aligned(4)));

uint8_t curr_font = 0;

const int gui_font_count = FONT_COUNT;

const lang_t *gui_lang[] = {
    &lang_en_us,
#if INCLUDED_ES_ES == 1
    &lang_es_es,
#endif
#if INCLUDED_PT_PT == 1
    &lang_pt_pt,
#endif
#if INCLUDED_FR_FR == 1
    &lang_fr_fr,
#endif
#if INCLUDED_IT_IT == 1
    &lang_it_it,
#endif
#if INCLUDED_DE_DE == 1
    &lang_de_de,
#endif
#if INCLUDED_RU_RU == 1
    &lang_ru_ru,
#endif
#if INCLUDED_ZH_CN == 1
    &lang_zh_cn,
#endif
#if INCLUDED_ZH_TW == 1
    &lang_zh_tw,
#endif
#if INCLUDED_KO_KR == 1
    &lang_ko_kr,
#endif
#if INCLUDED_JA_JP == 1
    &lang_ja_jp,
#endif
};

lang_t *curr_lang = &lang_en_us;
const int gui_lang_count = sizeof(gui_lang) / sizeof(*gui_lang);

int utf8_decode(const char *str, uint32_t *codepoint) {
    if (!str || !codepoint) return 0;

    unsigned char c = str[0];
    if (c < 0x80) {
        *codepoint = c;
        return 1; // Single-byte ASCII
    } else if ((c & 0xE0) == 0xC0) {
        *codepoint = ((c & 0x1F) << 6) | (str[1] & 0x3F);
        return 2; // Two-byte sequence
    } else if ((c & 0xF0) == 0xE0) {
        *codepoint = ((c & 0x0F) << 12) | ((str[1] & 0x3F) << 6) | (str[2] & 0x3F);
        return 3; // Three-byte sequence
    } else if ((c & 0xF8) == 0xF0) {
        *codepoint = ((c & 0x07) << 18) | ((str[1] & 0x3F) << 12) | ((str[2] & 0x3F) << 6) | (str[3] & 0x3F);
        return 4; // Four-byte sequence
    }

    printf("Invalid UTF-8 byte sequence\n");
    return 0;
}

int i18n_get_char_width(uint32_t codepoint)
{
    char *font;
    if (codepoint < 0x100) {
        font = gui_fonts[curr_font];
        return font[codepoint]; // Basic Latin (ASCII) characters
    } else if (codepoint >= 0x410 && codepoint <= 0x44F) {
            codepoint = codepoint - 0x410 + 0xC0; // 0x400 utf8 codepoint is 0x80 in cp1251 font
        font = cp1251_fonts[curr_font];
        return font[codepoint]; // Cyrillic characters
    } else if (codepoint >= 0x4E00 && codepoint <= 0x9FFF) {
        return 12; // CJK Unified Ideographs
    } else if (codepoint >= 0x1100 && codepoint <= 0x11FF) {
        return 12; // Hangul Jamo
    } else {
        return 8; // Default width for other Unicode characters
    }
}

int i18n_get_text_height()
{
    return 12;
}

int i18n_get_text_width(const char *text, const lang_t* lang)
{
    if (!text) return 0;

    int width = 0;
    uint32_t codepoint;
    int bytes;
    while (*text) {
        bytes = utf8_decode(text, &codepoint);
        if (bytes == 0) break; // Invalid sequence
        width += i18n_get_char_width(codepoint);
        text += bytes;
    }

    return width;
};

int i18n_get_text_lines(const char *text, const int fix_width, const lang_t* lang)
{
    if (text == NULL || text[0] == '\0') return 0;

    int w = 0;             // Current line width
    int lines = 1;         // Number of lines
    uint32_t codepoint;    // Decoded UTF-8 codepoint
    int bytes;             // Number of bytes in the UTF-8 sequence
    const char *current = text;

    while (*current) {
        if (*current == '\n') {
            // Newline resets line width
            lines++;
            w = 0;
            current++;
            continue;
        }

        bytes = utf8_decode(current, &codepoint);
        if (bytes == 0) break; // Invalid UTF-8 sequence

        // Determine character width based on the Unicode code point
        int char_width = i18n_get_char_width(codepoint);

        // Check if the character fits in the current line
        if ((fix_width - w) < char_width) {
            lines++;
            w = 0;
        }

        w += char_width;
        current += bytes; // Advance to the next character
    }

    return lines;
}

void odroid_overlay_read_screen_rect(uint16_t x_pos, uint16_t y_pos, uint16_t width, uint16_t height)
{
    uint16_t *dst_img = (uint16_t *)(lcd_get_active_buffer());
    for (int x = 0; x < width; x++)
        for (int y = 0; y < height; y++)
            overlay_buffer[x + y * width] = dst_img[(y + y_pos) * ODROID_SCREEN_WIDTH + x_pos + x];
}

int i18n_draw_text_line(uint16_t x_pos, uint16_t y_pos, uint16_t width, const char *text, uint16_t color, uint16_t color_bg, char transparent, const lang_t* lang)
{
    if (text == NULL || text[0] == 0)
        return 0;
    int font_height = 12;
    int x_offset = 0;
    char *font = gui_fonts[curr_font];

    if (transparent)
        odroid_overlay_read_screen_rect(x_pos, y_pos, width, font_height);
    else
    {
        for (int x = 0; x < width; x++)
            for (int y = 0; y < font_height; y++)
                overlay_buffer[x + y * width] = color_bg;
    }
#if 0 // TODO: Implement text clipping
    int w = i18n_get_text_width(text, lang);
    sprintf(realtxt, "%.*s", 160, text);
    // if text is too long, cut it and paint end point
    if (w > width)
    {
        w = 0;
        int i = 0;
        while (w < width)
        {
            w += font[realtxt[i]];
            i++;
        }
        realtxt[i - 1] = 0;
        // paint end point
        overlay_buffer[width * (font_height - 3) - 1] = get_darken_pixel(color, 80);
        overlay_buffer[width * (font_height - 3) - 3] = get_darken_pixel(color, 80);
        overlay_buffer[width * (font_height - 3) - 6] = get_darken_pixel(color, 80);
    };
#endif
    uint32_t codepoint;
    int bytes;
    while (*text) {
        bytes = utf8_decode(text, &codepoint);
        if (bytes == 0) break; // Invalid sequence
        text += bytes;

        if (codepoint < 0x100) {
            char *draw_font = font;
            int cw = draw_font[codepoint]; // width;
            if ((x_offset + cw) > width)
                break;
            if (cw != 0)
            {
                int d_pos = draw_font[codepoint * 2 + 0x100] + draw_font[codepoint * 2 + 0x101] * 0x100; // data pos
                int line_bytes = (cw + 7) / 8;
                for (int y = 0; y < font_height; y++)
                {
                    uint32_t *pixels_data = (uint32_t *)&(draw_font[0x300 + d_pos + y * line_bytes]);
                    int offset = x_offset + (width * y);

                    for (int x = 0; x < cw; x++)
                    {
                        if (pixels_data[0] & (1 << x))
                            overlay_buffer[offset + x] = color;
                    }
                }
            }
            x_offset += cw;
        } else if (codepoint >= 0x410 && codepoint <= 0x44F) {
            codepoint = codepoint - 0x410 + 0xC0; // 0x400 utf8 codepoint is 0x80 in cp1251 font
            char *draw_font = cp1251_fonts[curr_font];
            int cw = draw_font[codepoint]; // width;
            if ((x_offset + cw) > width)
                break;
            if (cw != 0)
            {
                int d_pos = draw_font[codepoint * 2 + 0x100] + draw_font[codepoint * 2 + 0x101] * 0x100; // data pos
                int line_bytes = (cw + 7) / 8;
                for (int y = 0; y < font_height; y++)
                {
                    uint32_t *pixels_data = (uint32_t *)&(draw_font[0x300 + d_pos + y * line_bytes]);
                    int offset = x_offset + (width * y);

                    for (int x = 0; x < cw; x++)
                    {
                        if (pixels_data[0] & (1 << x))
                            overlay_buffer[offset + x] = color;
                    }
                }
            }
            x_offset += cw;
        }
    }

    odroid_display_write(x_pos, y_pos, width, font_height, overlay_buffer);
    return font_height;
}

int i18n_draw_text(uint16_t x_pos, uint16_t y_pos, uint16_t width, uint16_t max_height, const char *text, uint16_t color, uint16_t color_bg, char transparent, const lang_t* lang)
{
    int text_len = 1;
    int height = 0;

    if (text == NULL || text[0] == 0)
        text = " ";

    text_len = strlen(text);
    if (x_pos < 0)
        x_pos = ODROID_SCREEN_WIDTH + x_pos;

    if (width < 1)
        width = i18n_get_text_width(text, lang);

    if (width > (ODROID_SCREEN_WIDTH - x_pos))
        width = (ODROID_SCREEN_WIDTH - x_pos);

    uint32_t codepoint;
    int line_len = 160; // min width is 2, max 160 char everline;
    char buffer_utf8[line_len + 1];
    int buffer_utf8_pos = 0;

    for (int pos = 0; pos < text_len;)
    {
        if ((height + i18n_get_text_height()) > max_height)
            break;
        // Build a single line buffer
        int w = 0;
        int bytes;
        buffer_utf8_pos = 0;
        while (*text)
        {
            bytes = utf8_decode(text, &codepoint);
            if (bytes == 0) break; // Invalid sequence
            int chr_width = i18n_get_char_width(codepoint);

            memcpy(buffer_utf8 + buffer_utf8_pos, text, bytes);

            if ((codepoint == '\n') ||
                (codepoint == 0) ||
                ((width - w) < chr_width))
            {
                break;
            }
            buffer_utf8_pos += bytes;
            text += bytes;
            w += chr_width;
        }
        buffer_utf8[buffer_utf8_pos] = 0;

        height += i18n_draw_text_line(x_pos, y_pos + height, width, buffer_utf8, color, color_bg, transparent, lang);
        pos += strlen(buffer_utf8);
    }

    return height;
}
