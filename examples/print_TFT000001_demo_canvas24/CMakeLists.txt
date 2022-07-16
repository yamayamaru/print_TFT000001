cmake_minimum_required(VERSION 3.12)

# Pull in PICO SDK (must be before project)
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(print_TFT000001_demo_canvas24_project)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Initialize the SDK
pico_sdk_init()

add_executable(
       print_TFT000001_demo_canvas24  print_TFT000001_demo_canvas24.cpp 
                                    print_TFT000001_Canvas24.cpp
                                    print_TFT000001.cpp
                                    font_class.cpp
                                    TFT000001.cpp
)

pico_generate_pio_header(print_TFT000001_demo_canvas24
                                ${CMAKE_CURRENT_LIST_DIR}/pio_8bit_parallel.pio
)

target_link_libraries(print_TFT000001_demo_canvas24
                       pico_stdlib
                       hardware_spi
                       hardware_pio
)

pico_enable_stdio_usb(print_TFT000001_demo_canvas24 0)
pico_enable_stdio_uart(print_TFT000001_demo_canvas24 1)

pico_add_extra_outputs(print_TFT000001_demo_canvas24)

