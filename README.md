*****************************************************************
*****************************************************************
**          Template STM32F4 Project @ psobek                  **
*****************************************************************
*****************************************************************

Choose appropriate startup for your particular microcontroller, e.g.:
`~$ cp ./lib/CMSIS/src/template/startup_stm32f40_41xxx.s ./lib/CMSIS/src/startup_stm32f40_41xxx.S`

Choose appropriate microcontroller by uncommenting #define in:
`./lib/CMSIS/inc/stm32f4xx.h`

Toolchain, cmake & st-link  installation:
`~$ sudo apt-get install -y cmake stlink-tools gcc-arm-none-eabi`

Makefiles generation:
`~$ cmake .`
or
`~$ cmake -D CMAKE_BUILD_TYPE=Release .`

Build:
`~$ make all`

Flash:
`~$ make flash`
