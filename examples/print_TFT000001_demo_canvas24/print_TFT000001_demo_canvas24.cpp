/*
    Raspberry Pi Pico pico-sdk LCD ILI9341 ILI9486 font print Library (C++)
    Demo Program
                                      https://twitter.com/yama23238
*/

#include <stdio.h>
#include "pico/stdlib.h"
#include "print_TFT000001.h"
#include "glcdfont.h"
#include "glcdfont_tt14.h"
#include "glcdfont_tt24.h"
#include "glcdfont_tt32.h"


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
glcdfont glcdfont01 = glcdfont();
glcdfont_tt14 glcdfont_tt14_01 = glcdfont_tt14();
glcdfont_tt24 glcdfont_tt24_01 = glcdfont_tt24();
glcdfont_tt32 glcdfont_tt32_01 = glcdfont_tt32();



void loop01(void);
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
    loop01();
    loop02_setup();
    loop02();
  }
  return 0;
}

void loop01(void) {
  static int r = 0;

  tft.set_rotation(r);
  tft.fillScreen(TFT000001_24BIT_COLOR_BLACK);
  tft.set_font_back_ground_fill(false);

  tft.set_font(&glcdfont_tt14_01);
  tft.set_font_color(tft.color(128, 255, 255), tft.color(0, 0, 0));
  tft.set_font_pos(0,  0);
  tft.fillScreen(TFT000001_24BIT_COLOR_BLACK);
  const char c[] = "ARM architecture (Jan.25,2022,20:57 UTC). In Wikipedia: The Free Encyclopedia. Retrieved from https://en.wikipedia.org/wiki/ARM_architecture";
  tft.word_print(c);
  sleep_ms(3000);



  tft.set_font(&glcdfont01);
  tft.set_font_color(tft.color(255, 255, 255), tft.color(0, 0, 0));
  tft.set_font_pos(0,  0);
  tft.fillScreen(TFT000001_24BIT_COLOR_BLACK);
  const char a[] = "ARM (stylised in lowercase as arm, formerly an acronym for Advanced RISC Machines and originally Acorn RISC Machine) is a family of reduced instruction set computer (RISC) architectures for computer processors, configured for various environments. Arm Ltd. develops the architecture and licenses it to other companies, who design their own products that implement one or more of those architectures, including system on a chip (SoC) and system on module (SoM) designs, that incorporate different components such as memory, interfaces, and radios. It also designs cores that implement these instruction set architectures and licenses these designs to many companies that incorporate those core designs into their own products. ";
  char b[2048];
  strcpy(b, a);
  tft.word_print(b);
  sleep_ms(3000);

  tft.set_font(&glcdfont01);
  tft.set_font_color(tft.color(255, 255, 255), tft.color(0, 0, 0));
  tft.set_font_pos(0,  0);
  tft.fillScreen(TFT000001_24BIT_COLOR_BLACK);
  tft.print(b);
  sleep_ms(3000);



  tft.set_font(&glcdfont01);
  tft.set_font_color(tft.color(0, 255, 255), tft.color(0, 0, 0));
  tft.set_font_pos(0,  0);
  tft.fillScreen(TFT000001_24BIT_COLOR_BLACK);
  tft.word_printf("color = 0x%04x,  %s\n", tft.color(0, 255, 255), "ARM (stylised in lowercase as arm, formerly an acronym for Advanced RISC Machines and originally Acorn RISC Machine) is a family of reduced instruction set computer (RISC) architectures for computer processors, configured for various environments. Arm Ltd. develops the architecture and licenses it to other companies, who design their own products that implement one or more of those architectures, including system on a chip (SoC) and system on module (SoM) designs, that incorporate different components such as memory, interfaces, and radios. It also designs cores that implement these instruction set architectures and licenses these designs to many companies that incorporate those core designs into their own products. ");
  sleep_ms(3000);

  tft.set_font(&glcdfont_tt14_01);
  tft.set_font_pos(0, 0);
  tft.fillScreen(TFT000001_24BIT_COLOR_BLACK);
  tft.word_printf("color = 0x%04x,  %s\n", tft.color(0, 255, 255), "ARM (stylised in lowercase as arm, formerly an acronym for Advanced RISC Machines and originally Acorn RISC Machine) is a family of reduced instruction set computer (RISC) architectures for computer processors, configured for various environments. Arm Ltd. develops the architecture and licenses it to other companies, who design their own products that implement one or more of those architectures, including system on a chip (SoC) and system on module (SoM) designs, that incorporate different components such as memory, interfaces, and radios. It also designs cores that implement these instruction set architectures and licenses these designs to many companies that incorporate those core designs into their own products. ");
  sleep_ms(3000);

  tft.set_font(&glcdfont_tt24_01);
  tft.set_font_pos(0, 0);
  tft.fillScreen(TFT000001_24BIT_COLOR_BLACK);
  tft.word_printf("color = 0x%04x,  %s\n", tft.color(0, 255, 255), "ARM (stylised in lowercase as arm, formerly an acronym for Advanced RISC Machines and originally Acorn RISC Machine) is a family of reduced instruction set computer (RISC) architectures for computer processors, configured for various environments. \n");
  sleep_ms(3000);

  tft.set_font(&glcdfont_tt32_01);
  tft.set_font_pos(0, 0);
  tft.fillScreen(TFT000001_24BIT_COLOR_BLACK);
  tft.word_printf("color = 0x%04x,  %s\n", tft.color(0, 255, 255), "ARM (stylised in lowercase as arm, formerly an acronym for Advanced RISC Machines and originally Acorn RISC Machine) is a family of reduced instruction set computer (RISC) architectures for computer processors, configured for various environments. \n");
  sleep_ms(3000);



  tft.set_font(&glcdfont01);
  tft.set_font_color(tft.color(0, 0, 255), tft.color(0, 0, 0));
  tft.set_font_pos(0,  0);
  tft.fillScreen(TFT000001_24BIT_COLOR_BLACK);
  tft.printf("color = 0x%04x,  %s\n", tft.color(0, 0, 255), "ARM (stylised in lowercase as arm, formerly an acronym for Advanced RISC Machines and originally Acorn RISC Machine) is a family of reduced instruction set computer (RISC) architectures for computer processors, configured for various environments. Arm Ltd. develops the architecture and licenses it to other companies, who design their own products that implement one or more of those architectures, including system on a chip (SoC) and system on module (SoM) designs, that incorporate different components such as memory, interfaces, and radios. It also designs cores that implement these instruction set architectures and licenses these designs to many companies that incorporate those core designs into their own products. ");
  sleep_ms(3000);

  tft.set_font(&glcdfont_tt14_01);
  tft.set_font_pos(0, 0);
  tft.fillScreen(TFT000001_24BIT_COLOR_BLACK);
  tft.printf("color = 0x%04x,  %s\n", tft.color(0, 0, 255), "ARM (stylised in lowercase as arm, formerly an acronym for Advanced RISC Machines and originally Acorn RISC Machine) is a family of reduced instruction set computer (RISC) architectures for computer processors, configured for various environments. Arm Ltd. develops the architecture and licenses it to other companies, who design their own products that implement one or more of those architectures, including system on a chip (SoC) and system on module (SoM) designs, that incorporate different components such as memory, interfaces, and radios. It also designs cores that implement these instruction set architectures and licenses these designs to many companies that incorporate those core designs into their own products. ");
  sleep_ms(3000);

  tft.set_font(&glcdfont_tt24_01);
  tft.set_font_pos(0, 0);
  tft.fillScreen(TFT000001_24BIT_COLOR_BLACK);
  tft.printf("color = 0x%04x,  %s\n", tft.color(0, 0, 255), "ARM (stylised in lowercase as arm, formerly an acronym for Advanced RISC Machines and originally Acorn RISC Machine) is a family of reduced instruction set computer (RISC) architectures for computer processors, configured for various environments.\n");
  sleep_ms(3000);

  tft.set_font(&glcdfont_tt32_01);
  tft.set_font_pos(0, 0);
  tft.fillScreen(TFT000001_24BIT_COLOR_BLACK);
  tft.printf("color = 0x%04x,  %s\n", tft.color(0, 0, 255), "ARM (stylised in lowercase as arm, formerly an acronym for Advanced RISC Machines and originally Acorn RISC Machine) is a family of reduced instruction set computer (RISC) architectures for computer processors, configured for various environments.\n");
  sleep_ms(3000);



  tft.set_font(&glcdfont01);
  tft.set_font_color(tft.color(0, 255, 0), tft.color(0, 0, 0));
  tft.set_font_pos(0,  0);
  tft.fillScreen(TFT000001_24BIT_COLOR_BLACK);
  tft.word_print("ARM (stylised in lowercase as arm, formerly an acronym for Advanced RISC Machines and originally Acorn RISC Machine) is a family of reduced instruction set computer (RISC) architectures for computer processors, configured for various environments. Arm Ltd. develops the architecture and licenses it to other companies, who design their own products that implement one or more of those architectures, including system on a chip (SoC) and system on module (SoM) designs, that incorporate different components such as memory, interfaces, and radios. It also designs cores that implement these instruction set architectures and licenses these designs to many companies that incorporate those core designs into their own products. \n");
  sleep_ms(3000);

  tft.set_font(&glcdfont_tt14_01);
  tft.set_font_pos(0, 0);
  tft.fillScreen(TFT000001_24BIT_COLOR_BLACK);
  tft.word_print("ARM (stylised in lowercase as arm, formerly an acronym for Advanced RISC Machines and originally Acorn RISC Machine) is a family of reduced instruction set computer (RISC) architectures for computer processors, configured for various environments. Arm Ltd. develops the architecture and licenses it to other companies, who design their own products that implement one or more of those architectures, including system on a chip (SoC) and system on module (SoM) designs, that incorporate different components such as memory, interfaces, and radios. It also designs cores that implement these instruction set architectures and licenses these designs to many companies that incorporate those core designs into their own products. \n");
  sleep_ms(3000);

  tft.set_font(&glcdfont_tt24_01);
  tft.set_font_pos(0, 0);
  tft.fillScreen(TFT000001_24BIT_COLOR_BLACK);
  tft.word_print("ARM (stylised in lowercase as arm, formerly an acronym for Advanced RISC Machines and originally Acorn RISC Machine) is a family of reduced instruction set computer (RISC) architectures for computer processors, configured for various environments. \n");
  sleep_ms(3000);

  tft.set_font(&glcdfont_tt32_01);
  tft.set_font_pos(0, 0);
  tft.fillScreen(TFT000001_24BIT_COLOR_BLACK);
  tft.word_print("ARM (stylised in lowercase as arm, formerly an acronym for Advanced RISC Machines and originally Acorn RISC Machine) is a family of reduced instruction set computer (RISC) architectures for computer processors, configured for various environments. ");
  sleep_ms(3000);



  tft.set_font(&glcdfont01);
  tft.set_font_color(tft.color(255, 0, 255), tft.color(0, 0, 0));
  tft.set_font_pos(0,  0);
  tft.fillScreen(TFT000001_24BIT_COLOR_BLACK);
  tft.print("ARM (stylised in lowercase as arm, formerly an acronym for Advanced RISC Machines and originally Acorn RISC Machine) is a family of reduced instruction set computer (RISC) architectures for computer processors, configured for various environments. Arm Ltd. develops the architecture and licenses it to other companies, who design their own products that implement one or more of those architectures, including system on a chip (SoC) and system on module (SoM) designs, that incorporate different components such as memory, interfaces, and radios. It also designs cores that implement these instruction set architectures and licenses these designs to many companies that incorporate those core designs into their own products. \n");
  sleep_ms(3000);

  tft.set_font(&glcdfont_tt14_01);
  tft.set_font_pos(0, 0);
  tft.fillScreen(TFT000001_24BIT_COLOR_BLACK);
  tft.print("ARM (stylised in lowercase as arm, formerly an acronym for Advanced RISC Machines and originally Acorn RISC Machine) is a family of reduced instruction set computer (RISC) architectures for computer processors, configured for various environments. Arm Ltd. develops the architecture and licenses it to other companies, who design their own products that implement one or more of those architectures, including system on a chip (SoC) and system on module (SoM) designs, that incorporate different components such as memory, interfaces, and radios. It also designs cores that implement these instruction set architectures and licenses these designs to many companies that incorporate those core designs into their own products. \n");
  sleep_ms(3000);

  tft.set_font(&glcdfont_tt24_01);
  tft.set_font_pos(0, 0);
  tft.fillScreen(TFT000001_24BIT_COLOR_BLACK);
  tft.print("ARM (stylised in lowercase as arm, formerly an acronym for Advanced RISC Machines and originally Acorn RISC Machine) is a family of reduced instruction set computer (RISC) architectures for computer processors, configured for various environments. \n");
  sleep_ms(3000);

  tft.set_font(&glcdfont_tt32_01);
  tft.set_font_pos(0, 0);
  tft.fillScreen(TFT000001_24BIT_COLOR_BLACK);
  tft.print("ARM (stylised in lowercase as arm, formerly an acronym for Advanced RISC Machines and originally Acorn RISC Machine) is a family of reduced instruction set computer (RISC) architectures for computer processors, configured for various environments.\n");
  sleep_ms(3000);

  r++;
  if (r >= 4) r = 0;
}




#include "print_TFT000001_Canvas24.h"

#define CIRCLE_N   80
#define RDX         5
#define RDY         5

#define CANVAS_WIDTH  160
#define CANVAS_HEIGHT 213

print_TFT000001_Canvas24 canvas01 = print_TFT000001_Canvas24(CANVAS_WIDTH, CANVAS_HEIGHT);
    // print_TFT000001_Canvas24はメモリ上の確保したフレームバッファ上に描画するクラスです。
    // print_TFT000001_Canvas24でメモリ上に書き込んだうえで
    // print_TFT000001もしくはTFT000001のdrawRGBBitmap24()で
    // 実際にILI9341またはILI9486のLCDにフレームバッファのメモリの内容を
    // 一度に書き込むことで高速に描画ができます。
    // print_TFT000001_Canvas24を使う場合はCMakeLists.txtのadd_executableに
    // print_TFT000001_Canvas24.cppを追加するのを忘れないようにしてください


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
    canvas01.setRotation(r);
    canvas01.set_font(&glcdfont_tt24_01);
    canvas01.set_font_color(TFT000001_24BIT_COLOR_MAGENTA, TFT000001_24BIT_COLOR_BLACK);
    canvas01.set_font_pos(0,  0);

    for (int i = 0; i < CIRCLE_N; i++) {
        circle01[i].x = rnd(canvas01.width());
        circle01[i].y = rnd(canvas01.height());
        circle01[i].r = rnd(10) + 5;
        circle01[i].c = rnd(16777215) + 1;
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
    canvas01.fillScreen(TFT000001_24BIT_COLOR_BLACK);
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
    tft.drawRGBBitmap24((TFT000001_TFT_WIDTH - CANVAS_WIDTH) / 2, (TFT000001_TFT_HEIGHT - CANVAS_HEIGHT) / 2, canvas01.getBuffer(), CANVAS_WIDTH, CANVAS_HEIGHT); 
    sleep_ms(10);
}

int rnd(int a) {
    return (rand() % a);
}
