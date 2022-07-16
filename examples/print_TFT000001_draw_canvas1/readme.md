# examples print_TFT000001_draw_canvas1
  
このプログラムはpico-sdk用ですpico-sdkを使ってビルドしてください。
ビルドするにはTFT000001、print_TFT000001が必要になります。  
https://github.com/yamayamaru/TFT000001  
https://github.com/yamayamaru/print_TFT000001  

  
CMakeLists.txt  
print_TFT000001_draw_canvas1.cpp  
font_class.h  
font_class.cpp  
glcdfont.h  
glcdfont_tt14.h  
glcdfont_tt24.h  
glcdfont_tt32.h  
print_TFT000001_Canvas1.h  
print_TFT000001_Canvas1.cpp  
print_TFT000001_Canvas8.h  
print_TFT000001_Canvas8.cpp  
print_TFT000001_Canvas16.h  
print_TFT000001_Canvas16.cpp  
print_TFT000001_Canvas24.h  
print_TFT000001_Canvas24.cpp  
print_TFT000001.h  
print_TFT000001.cpp  
TFT000001.h  
TFT000001.cpp  
pio_8bit_parallel.pio
TFT000001_config.h
  
上記ファイルを同じディレクトリに入れてビルドしてください。  
ビルド前にTFT000001_config.hの中で  
ILI9341なのか、ILI9486なのか(ILI9341なら#define TFT000001_ILI9486_DISPLAYをコメントアウト)  
PIOなのかSPIなのか(SPIなら#define TFT000001_PIO_8BIT_PARALELLをコメントアウト)  
の設定を必ずしてください。  
  
CMakeLists.txtでpico-sdkのprintfの出力がUART0になっています。  
USBシリアルに出力したい場合はCMakeLists.txtの最後の方の3行を下記のように変更してください。  
  
    pico_enable_stdio_usb(print_GFX_graphicstest 1)
    pico_enable_stdio_uart(print_GFX_graphicstest 0)
    
    pico_add_extra_outputs(print_GFX_graphicstest)
  
  
