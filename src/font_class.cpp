// font_class.cpp
//
//    print_GFX_ILI9341 LCD ILI9341 font print Library (C++)
//                                   https://twitter.com/yama23238
//

#include "font_class.h"

int32_t font_class01::height() {
    return 8;
}

int32_t font_class01::max_width() {
    return 6;
}

bool font_class01::hmap() {
    return false;
}

bool font_class01::reverse() {
        return false;
}

bool font_class01::monospaced() {
    return true;
}

int32_t font_class01::min_ch() {
    return 0;
}

int32_t font_class01::max_ch() {
    return 255;
}

int32_t font_class01::get_width(const char *str, int32_t size) {
    return (strnlen(str, size) * 6);
}

int32_t font_class01::get_ch_char_w(char ch) {
    return 6;
}

void font_class01::get_ch(char ch, uint8_t **buf) {
    for (int i = 0; i < 6; i++) {
        (*buf)[i] = 0xff;
    }
}