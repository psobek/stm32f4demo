---
---
# Template STM32F4 Project @ psobek
---
---

## HOWTO:

* Choose appropriate startup for your particular microcontroller, e.g.: <br>
`~$ cp ./lib/CMSIS/src/template/startup_stm32f40_41xxx.s ./lib/CMSIS/src/startup_stm32f40_41xxx.S`

* Choose appropriate microcontroller by uncommenting #define in:<br>
`./lib/CMSIS/inc/stm32f4xx.h`

* Toolchain, cmake & st-link installation:<br>
`~$ sudo apt-get install -y cmake stlink-tools gcc-arm-none-eabi`

* Makefiles generation:<br>
`~$ cmake .`
or <br>
`~$ cmake -D CMAKE_BUILD_TYPE=Release .`

* Build:<br>
`~$ make all`

* Flash:<br>
`~$ make flash`

## LICENSE

- STM32F libraries license: `ULTIMATE LIBERTY SOFTWARE LICENSE`
- project itself: MIT License
