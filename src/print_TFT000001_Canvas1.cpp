// print_TFT000001_Canvas1.cpp
// Version 0.0.1
//
//    print_TFT000001 LCD ILI9341 ILI9486 font print Library (C++)
//                                   https://twitter.com/yama23238
//
//    このプログラムはmicropython-ili9341を参考にして作成しました
//    https://github.com/jeffmer/micropython-ili9341
//
//    Copyright (c) 2017 Jeffrey N. Magee
//    Released under the MIT license
//    https://github.com/jeffmer/micropython-ili9341/blob/master/LICENSE

#include "print_TFT000001_Canvas1.h"

print_TFT000001_Canvas1::print_TFT000001_Canvas1(int16_t w, int16_t h) :
  yama_2_GFX_H_beta_Canvas1(w, h) {

    _scroll = 0;
    _colormap.fg = 0xffff;
    _colormap.bg = 0x0000;
    _x = 0;
    _y = 0;
    scrolling = false;
    _back_ground_fill_flag = false;
    _font_class01_dummy = font_class01();
    _font = &_font_class01_dummy;
}

void print_TFT000001_Canvas1::set_font_color(uint32_t fg, uint32_t bg) {
    _colormap.fg = fg;
    _colormap.bg = bg;
}

void print_TFT000001_Canvas1::set_font_pos(int32_t x, int32_t y) {
    _x = x;
    _y = y;
}

void print_TFT000001_Canvas1::set_font(font_class01 *font) {
    _font = font;
}

bool print_TFT000001_Canvas1::get_bit(uint8_t *glyph, int32_t ch) {
    int32_t bit, byte;
    bit = ch % 8;
    byte = ch / 8;
    if (((uint32_t)glyph[byte] & (uint32_t)(0x01 << bit)) > 0) {
        return true;
    } else {
        return false;
    }
}

void print_TFT000001_Canvas1::clear_memory(uint8_t *buf, uint8_t value, uint32_t num){
    for (int32_t i = 0; i < num; i++) {
        buf[i] = value;
    }
}

int32_t print_TFT000001_Canvas1::chars(const char *str, int32_t x, int32_t y) {
    int32_t str_w, div, rem, nbytes, index;
    uint8_t *glyph;
    int32_t char_w, pos;

    str_w = _font->get_width(str, _PRINT_TFT000001_Canvas1_MAX_TEXT_SIZE01);
    div = _font->height() / 8;
    rem = _font->height() % 8;
    if (rem == 0) nbytes = div;
    else          nbytes = div + 1;

    pos = 0;
    glyph = glyph_buff01;
    int32_t str_len02 = strnlen(str, _PRINT_TFT000001_Canvas1_MAX_TEXT_SIZE01);
    for (int32_t ci = 0; ci < str_len02; ci++) {
        char ch = str[ci];
        char_w = _font->get_ch_char_w(ch);
        clear_memory(glyph, 0, char_w * nbytes);
        _font->get_ch(ch, &glyph);

        for (int32_t xx = 0; xx < char_w; xx++) {
            for (int32_t yy = 0; yy < 8 * nbytes; yy++) {
                int32_t buf_index = xx * nbytes * 8 + yy;
                if (get_bit(glyph, buf_index)) {
                    drawPixel((int32_t)(x + xx + pos), (int32_t)(y + yy), _colormap.fg);
                } else {
                    if (_back_ground_fill_flag)
                        drawPixel((int32_t)(x + xx + pos), (int32_t)(y + yy), _colormap.bg);
                }
            }
        }
        pos += char_w;
    }

    return (x + str_w);
}

int32_t print_TFT000001_Canvas1::next_line(int32_t cury, int32_t char_h) {
    int32_t res;

    res = cury + char_h;

    return res;
}

int print_TFT000001_Canvas1::substr01(const char *source, char *dest, int buffsize, int start, int length) {
    char *sp, *ep, size;
    size = buffsize - 1;
    int32_t source_len01 = strnlen(source,  _PRINT_TFT000001_Canvas1_MAX_TEXT_SIZE01);

    sp = (char *)source + start;
    ep = (char *)source + start + length;
    if (sp > (source + source_len01)) {
        dest[0] = '\0';
        return -1;
    }
    if (ep > (source + source_len01)) {
        ep = ((char *)source + source_len01);
        length = ep - sp;
    }
    if (length > size) {
        length = size;
    }
    if (length < 0) {
        dest[0] = '\0';
        return -1;
    }
    memcpy(dest, sp, length);
    dest[length] = '\0';
    return 0;
}

void print_TFT000001_Canvas1::print(const char *text) { // does character wrap, compatible with stream output

    int32_t curx, cury, char_w, char_h, width1, written;
    int32_t str_len01;

    curx = _x;
    cury = _y;
    char_h = _font->height();
    width1 = 0;
    written = 0;

    str_len01 = strnlen(text, _PRINT_TFT000001_Canvas1_MAX_TEXT_SIZE01);
    if (str_len01 > _PRINT_TFT000001_Canvas1_STR_BUFF01_LEN01) return ;

    for (int32_t pos = 0; pos < str_len01; pos++) {
        char ch = text[pos];
        if (ch == '\n') {
            if (pos > 0) {
                substr01(text, str_buff01, _PRINT_TFT000001_Canvas1_STR_BUFF01_LEN01, written, pos - written);
                chars(str_buff01, curx, cury);
            }
            curx = 0;
            written = pos + 1;
            width1 = 0;
            cury = next_line(cury, char_h);
        } else {
            char_w = _font->get_ch_char_w(ch);
            if ((curx + width1 + char_w) >= _width) {
                substr01(text, str_buff01, _PRINT_TFT000001_Canvas1_STR_BUFF01_LEN01, written, pos - written);
                chars(str_buff01, curx, cury);
                curx = 0;
                written = pos;
                width1 = char_h;
                cury = next_line(cury, char_h);
            } else {
                width1 += char_w;
            }
        }
    }
    if (written < str_len01) {
        substr01(text, str_buff01, _PRINT_TFT000001_Canvas1_STR_BUFF01_LEN01, written, str_len01 - written);
        curx = chars(str_buff01, curx, cury);
    }
    _x = curx;
    _y = cury;
}

void print_TFT000001_Canvas1::word_print(std::string text) { // does word wrap, leaves self._x unchanged

    int32_t curx, cury, char_h, char_w;
    std::stringstream text_s{text};
    std::string lines;

    curx = _x;
    cury = _y;
    char_h = _font->height();
    char_w = _font->max_width();
    while (std::getline(text_s, lines, '\n')) {
        std::stringstream lines_s{lines};
        std::string buf;
        std::vector<std::string> words;
        while (std::getline(lines_s, buf, ' ')) {
            words.push_back(buf);
        }

        for (int i = 0; i < words.size(); i++) {
            std::string word = words[i];
            if ((curx + _font->get_width(word.c_str(), word.length())) >= _width) {
                curx = _x;
                cury = next_line(cury, char_h);
                while (_font->get_width(word.c_str(), word.length()) > _width) {
                    chars((word.substr(0, _width / char_w).c_str()), curx, cury);
                    word = word.substr(_width / char_w, word.length() - _width / char_w);
                    cury = next_line(cury, char_h);
                }
            }
            if (word.length() > 0) {
                curx = chars((word + ' ').c_str(), curx, cury);
            }
        }
        curx = _x;
        cury = next_line(cury, char_h);
    }
    _y = cury;
}

void print_TFT000001_Canvas1::set_font_back_ground_fill(bool flag) {
    _back_ground_fill_flag = flag;
}

#include <stdarg.h>
void print_TFT000001_Canvas1::printf(const char* format, ...) {

    char str_buff01[_PRINT_TFT000001_Canvas1_MAX_TEXT_SIZE01 + 1];

    va_list ap;
    va_start(ap, format);

    vsnprintf(str_buff01, _PRINT_TFT000001_Canvas1_MAX_TEXT_SIZE01, format, ap);

    print(str_buff01);

    va_end(ap);
}

void print_TFT000001_Canvas1::word_printf(const char* format, ...) {

    char str_buff01[_PRINT_TFT000001_Canvas1_MAX_TEXT_SIZE01 + 1];

    va_list ap;
    va_start(ap, format);

    vsnprintf(str_buff01, _PRINT_TFT000001_Canvas1_MAX_TEXT_SIZE01, format, ap);

    word_print(std::string(str_buff01));

    va_end(ap);
}
