// font_class.h
//
//    print_GFX_ILI9341 LCD ILI9341 font print Library (C++)
//                                   https://twitter.com/yama23238
//
#ifndef _FONT_CLASS01_H
#define _FONT_CLASS01_H
#include <stdint.h>
#include <string.h>
class font_class01 {
public:
    font_class01() {}
    virtual int32_t height();
    virtual int32_t max_width();
    virtual bool hmap();
    virtual bool reverse();
    virtual bool monospaced();
    virtual int32_t min_ch();
    virtual int32_t max_ch();
    virtual int32_t get_width(const char *str, int32_t size);
    virtual void get_ch(char ch, uint8_t **buf);
    virtual int32_t get_ch_char_w(char ch);
};

#endif // _FONT_CLASS01_H
