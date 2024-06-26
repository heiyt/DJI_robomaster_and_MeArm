/*******************************************************************************
 * Size: 48 px
 * Bpp: 1
 * Opts: --bpp 1 --size 48 --font D:/heiyt_R9000P/Documents/SquareLine/assets/iconfont_guanji.ttf -o D:/heiyt_R9000P/Documents/SquareLine/assets\ui_font_guanji48.c --format lvgl -r 0xe62c --no-compress --no-prefilter
 ******************************************************************************/

#include "../ui.h"

#ifndef UI_FONT_GUANJI48
#define UI_FONT_GUANJI48 1
#endif

#if UI_FONT_GUANJI48

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+E62C "" */
    0x0, 0x0, 0x78, 0x0, 0x0, 0x0, 0x0, 0xf0,
    0x0, 0x0, 0x1, 0xe1, 0xe0, 0x0, 0x0, 0x7,
    0xc3, 0xc1, 0xf0, 0x0, 0x3f, 0x87, 0x83, 0xf0,
    0x0, 0xfc, 0xf, 0x3, 0xf0, 0x3, 0xf0, 0x1e,
    0x3, 0xf0, 0x7, 0xc0, 0x3c, 0x3, 0xf0, 0x1f,
    0x0, 0x78, 0x3, 0xf0, 0x7c, 0x0, 0xf0, 0x3,
    0xe0, 0xf0, 0x1, 0xe0, 0x3, 0xe3, 0xe0, 0x3,
    0xc0, 0x3, 0xc7, 0x80, 0x7, 0x80, 0x7, 0xcf,
    0x0, 0xf, 0x0, 0x7, 0xbe, 0x0, 0x1e, 0x0,
    0xf, 0x78, 0x0, 0x3c, 0x0, 0xf, 0xf0, 0x0,
    0x78, 0x0, 0x1f, 0xe0, 0x0, 0xf0, 0x0, 0x3f,
    0xc0, 0x1, 0xe0, 0x0, 0x7f, 0x80, 0x3, 0xc0,
    0x0, 0xff, 0x0, 0x7, 0x80, 0x1, 0xfe, 0x0,
    0xf, 0x0, 0x3, 0xfe, 0x0, 0x1e, 0x0, 0x7,
    0xbc, 0x0, 0x0, 0x0, 0x1e, 0x78, 0x0, 0x0,
    0x0, 0x3c, 0xf8, 0x0, 0x0, 0x0, 0xf8, 0xf0,
    0x0, 0x0, 0x1, 0xe1, 0xf0, 0x0, 0x0, 0x7,
    0xc1, 0xf0, 0x0, 0x0, 0x1f, 0x3, 0xf0, 0x0,
    0x0, 0x3e, 0x3, 0xf0, 0x0, 0x1, 0xf8, 0x3,
    0xf0, 0x0, 0x7, 0xe0, 0x3, 0xf8, 0x0, 0x3f,
    0x80, 0x3, 0xfe, 0x3, 0xfe, 0x0, 0x3, 0xff,
    0xff, 0xf8, 0x0, 0x1, 0xff, 0xff, 0xc0, 0x0,
    0x0, 0xff, 0xfe, 0x0, 0x0, 0x0, 0x3f, 0xe0,
    0x0, 0x0
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 768, .box_w = 39, .box_h = 38, .ofs_x = 5, .ofs_y = -1}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/



/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 58924, .range_length = 1, .glyph_id_start = 1,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    }
};



/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

#if LV_VERSION_CHECK(8, 0, 0)
/*Store all the custom data of the font*/
static  lv_font_fmt_txt_glyph_cache_t cache;
static const lv_font_fmt_txt_dsc_t font_dsc = {
#else
static lv_font_fmt_txt_dsc_t font_dsc = {
#endif
    .glyph_bitmap = glyph_bitmap,
    .glyph_dsc = glyph_dsc,
    .cmaps = cmaps,
    .kern_dsc = NULL,
    .kern_scale = 0,
    .cmap_num = 1,
    .bpp = 1,
    .kern_classes = 0,
    .bitmap_format = 0,
#if LV_VERSION_CHECK(8, 0, 0)
    .cache = &cache
#endif
};


/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
#if LV_VERSION_CHECK(8, 0, 0)
const lv_font_t ui_font_guanji48 = {
#else
lv_font_t ui_font_guanji48 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 38,          /*The maximum line height required by the font*/
    .base_line = 1,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = 0,
    .underline_thickness = 0,
#endif
    .dsc = &font_dsc           /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
};



#endif /*#if UI_FONT_GUANJI48*/

