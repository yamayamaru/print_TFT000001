/*
    Raspberry Pi Pico pico-sdk LCD ILI9341 ILI9486 font print Library (C++)
    Demo Program
                                      https://twitter.com/yama23238
*/

#include <stdio.h>
#include "pico/stdlib.h"
#include "print_TFT000001.h"
#include "glcdfont_tt24.h"
#include "print_TFT000001_Canvas8.h"


#if !defined(TFT000001_PIO_8BIT_PARALELL)
  #define TFT_MOSI 19
  #define TFT_SCK  18
  #define TFT_CS   17
  #define TFT_MISO 16
  #define TFT_SPI_PORT spi0

  #define TFT_RST  22
  #define TFT_DC   20
#endif

#ifdef TFT000001_PIO_8BIT_PARALELL
  #define TFT_DC   14
  #define TFT_RST  15
  #define TFT_WR   22

  #define TFT_D0    6
  #define TFT_D1    7
  #define TFT_D2    8
  #define TFT_D3    9
  #define TFT_D4   10
  #define TFT_D5   11
  #define TFT_D6   12
  #define TFT_D7   13
#endif

#ifdef TFT000001_PIO_8BIT_PARALELL
  #include "hardware/pio.h"
  #include "pio_8bit_parallel.pio.h"
  print_TFT000001 tft = print_TFT000001(TFT_D0, TFT_WR, TFT_DC, TFT_RST, -1);
#else
  #include "hardware/spi.h"
  print_TFT000001 tft = print_TFT000001(TFT_SPI_PORT, TFT_DC, TFT_RST, TFT_CS);
#endif


// フォントの宣言
glcdfont_tt24 glcdfont_tt24_01 = glcdfont_tt24();


void loop02_setup(void);
void loop02(void);

int main() {

#ifdef TFT000001_PIO_8BIT_PARALELL
    tft.INIT_TFT_DATA_BUS();
#endif

#if !defined(TFT000001_PIO_8BIT_PARALELL)
  spi_init(TFT_SPI_PORT, 20000000);
  gpio_set_function(TFT_MISO, GPIO_FUNC_SPI);
  gpio_set_function(TFT_SCK, GPIO_FUNC_SPI);
  gpio_set_function(TFT_MOSI, GPIO_FUNC_SPI);
  gpio_pull_up(TFT_MISO);
  gpio_pull_up(TFT_SCK);
  gpio_pull_up(TFT_MOSI);
  spi_set_format(TFT_SPI_PORT, 8, SPI_CPOL_0, SPI_CPHA_0, SPI_MSB_FIRST);   // SPI MODE0, MSBFIRST
#endif
  sleep_ms(200);
  printf("\nReset:");
 
  tft.init(1);  // ILI9486の場合1なら18bitカラー、0なら16bitカラー
                // ILI9486でSPI接続の場合、18bitカラーのみ
                // ILI9341は16bitカラーのみ(パラメータは無視)
  sleep_ms(200); 

  tft.set_rotation(0);
  tft.fillScreen(TFT000001_24BIT_COLOR_BLACK);

  while (1) {
    loop02_setup();
    loop02();
  }
  return 0;
}



#define CIRCLE_N   80
#define RDX         5
#define RDY         5

#define CANVAS_WIDTH  TFT000001_TFT_WIDTH
#define CANVAS_HEIGHT TFT000001_TFT_HEIGHT

print_TFT000001_Canvas8 canvas01 = print_TFT000001_Canvas8(CANVAS_WIDTH, CANVAS_HEIGHT);
    // print_TFT000001_Canvas8はメモリ上の確保したフレームバッファ上に描画するクラスです。
    // print_TFT000001_Canvas8でメモリ上に書き込んだうえで
    // print_TFT000001もしくはTFT000001のdrawPalette256Bitmap()で
    // 実際にILI9341またはILI9486のLCDにフレームバッファのメモリの内容を
    // 一度に書き込むことで高速に描画ができます。
    // print_TFT000001_Canvas8を使う場合はCMakeLists.txtのadd_executableに
    // print_TFT000001_Canvas8.cppを追加するのを忘れないようにしてください


void random_circle(void);
void loop02(void) {
    tft.fillScreen(TFT000001_24BIT_COLOR_BLACK);
    int n = 100;
    for (int i = 0; i < n; i++) {
        random_circle();
    }
}

int rnd(int max);

struct {
    int    x;
    int    y;
    int    dx;
    int    dy;
    int    signx;
    int    signy;
    int    r;
    int    c;
} circle01[CIRCLE_N];

void loop02_setup(void) {
    static int r = 0;

    tft.set_rotation(0);
    canvas01.setWeb216Palette256();
    canvas01.setRotation(r);
    canvas01.set_font(&glcdfont_tt24_01);
    canvas01.set_font_color(YAMA_2_GFX_H_BETA_WEB216_PALETTE_MAGENTA, YAMA_2_GFX_H_BETA_WEB216_PALETTE_BLACK);
    canvas01.set_font_pos(0,  0);

    for (int i = 0; i < CIRCLE_N; i++) {
        circle01[i].x = rnd(canvas01.width());
        circle01[i].y = rnd(canvas01.height());
        circle01[i].r = rnd(10) + 5;
        circle01[i].c = rnd(255) + 1;
        circle01[i].dx = rnd(RDX) + 1;
        circle01[i].dy = rnd(RDY) + 1;
        circle01[i].signx = rnd(2) ? 1 : -1;
        circle01[i].signy = rnd(2) ? 1 : -1;
    }

    
    r++;
    if (r >=4) r = 0;
}

void random_circle(void) {

    int temp1, temp2;
    canvas01.fillScreen(YAMA_2_GFX_H_BETA_WEB216_PALETTE_BLACK);
    for (int i = 0; i < CIRCLE_N; i++ ) {
        temp1 = circle01[i].dx * circle01[i].signx;
        temp2 = circle01[i].x + temp1;
        if (temp2 > canvas01.width()) {
            circle01[i].signx = -1;
            circle01[i].dx = rnd(RDX) + 1;
            circle01[i].x = canvas01.width() + circle01[i].signx * circle01[i].dx;
        } else if (temp2 < 0 ) {
            circle01[i].signx = 1;
            circle01[i].dx = rnd(RDX) + 1;
            circle01[i].x = 0 + circle01[i].signx * circle01[i].dx;
        } else {
            circle01[i].x = circle01[i].x + temp1;
        } 
        temp1 = circle01[i].dy * circle01[i].signy;
        temp2 = circle01[i].y + temp1;
        if (temp2 > canvas01.height()) {
            circle01[i].signy = -1;
            circle01[i].dy = rnd(RDY) + 1;
            circle01[i].y = canvas01.height() + circle01[i].signy * circle01[i].dy;
        } else if (temp2 < 0 ) {
            circle01[i].signy = 1;
            circle01[i].dy = rnd(RDY) + 1;
            circle01[i].y = 0 + circle01[i].signy * circle01[i].dy;
        } else {
            circle01[i].y = circle01[i].y + temp1;
        }

        // フレームバッファ上に円を描画
        canvas01.fillCircle( circle01[i].x, circle01[i].y + 15, circle01[i].r, circle01[i].c);
    }

    // フレームバッファ上に文字を表示
    canvas01.set_font_pos(0, 0);
    canvas01.word_printf("Raspberry Pi Pico");

    // フレームバッファのメモリの内容を実際にILI9341のLCDに書き込む
    tft.drawPalette256Bitmap((TFT000001_TFT_WIDTH - CANVAS_WIDTH) / 2, (TFT000001_TFT_HEIGHT - CANVAS_HEIGHT) / 2, canvas01.getBuffer(), CANVAS_WIDTH, CANVAS_HEIGHT, canvas01.getPaletteTable256(tft.getColorMode())); 
    sleep_ms(10);
}

int rnd(int a) {
    return (rand() % a);
}
