#
# Template STM32F4 Firmware cmake file
#
# Platform STM32F4
#

cmake_minimum_required(VERSION 3.14.0)

project ( stm32f4template.elf )

enable_language(C)
enable_language(ASM)

set(CMAKE_COLOR_MAKEFILE ON)
set(CMAKE_VERBOSE_MAKEFILE OFF)

set(CMAKE_SYSTEM_NAME arm-none-eabi-)
set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_ASM_COMPILER arm-none-eabi-gcc)

set(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS "")

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  add_definitions(
    -DUSE_DEFAULT_CALLBACK
    -DUSE_STDPERIPH_DRIVER
    -DDEBUG
    -O0 -g3 -ggdb -Wall
    -c -mthumb -mcpu=cortex-m4 -mtune=cortex-m4 -mfloat-abi=hard -mfpu=auto -fdata-sections -ffunction-sections
  )
  set(CMAKE_EXE_LINKER_FLAGS "-T ./conf/stm32_flash.ld -mthumb -mcpu=cortex-m4 -mfloat-abi=hard -mfpu=auto -mtune=cortex-m4 -Wl,-Map=linker.map -Wl,-cref -Wl,--gc-sections -Wl,-lc -specs=nosys.specs -specs=nano.specs")

endif()

if(CMAKE_BUILD_TYPE STREQUAL "Release")
  add_definitions(
    -DUSE_DEFAULT_CALLBACK
    -DUSE_STDPERIPH_DRIVER
    -DNDEBUG
    -O3 -Wall
    -c -mthumb -mcpu=cortex-m4 -mtune=cortex-m4 -mfloat-abi=hard -mfpu=auto -fdata-sections -ffunction-sections
  )
  set(CMAKE_EXE_LINKER_FLAGS "-T ./conf/stm32_flash.ld -mthumb -mcpu=cortex-m4 -mfloat-abi=hard -mfpu=auto -mtune=cortex-m4 -Wl,-Map=linker.map -Wl,-cref -Wl,--strip-all -Wl,--gc-sections -Wl,-lc -specs=nosys.specs -specs=nano.specs")

endif()

include_directories(
    ./src
    ./conf/
    ./src/engine/
    ./headers/
    ./lib/CMSIS/inc
    ./lib/STM32F4xx_StdPeriph_Driver/inc/
    ./FreeRTOS/Source/include/
    ./FreeRTOS/Source/
    ./FreeRTOS/Source/portable/GCC/ARM_CM4F/
)

file(GLOB headers
    "./src/*.h"
    "./conf/*.h"
    "./src/engine/*.h"
    "./headers/*.h"
    "./lib/CMSIS/inc/*.h"
    "./lib/STM32F4xx_StdPeriph_Driver/inc/*.h"
    "./FreeRTOS/Source/include/*.h"
    "./FreeRTOS/Source/portable/GCC/ARM_CM4F/*.h"
)

file(GLOB sources
    "./src/*.c"
    "./conf/*.c"
    "./src/engine/*.c"
    "./headers/*.c"
    "./lib/CMSIS/src/*.c"
    "./lib/STM32F4xx_StdPeriph_Driver/src/*.c"
    "./lib/CMSIS/src/*.S"
    "./FreeRTOS/Source/tasks.c"
    "./FreeRTOS/Source/queue.c"
    "./FreeRTOS/Source/list.c"
    "./FreeRTOS/Source/portable/GCC/ARM_CM4F/port.c"
    "./FreeRTOS/Source/portable/MemMang/heap_4.c"
)

add_executable(${PROJECT_NAME} ${sources})

# Flashing using st-flash tool for ST-LINK/v2
add_custom_target(flash)
add_custom_command(TARGET flash
    COMMAND st-flash --reset write ./images/stm32f4template.bin 0x08000000
)

# Generating custom header files
#add_custom_target(prebuild)
#add_custom_command(TARGET prebuild
#    PRE_BUILD
#    COMMAND ./scripts/prebuild.sh
#    DEPENDS ${PROJECT_NAME}
#)
#add_dependencies(${PROJECT_NAME} prebuild)

# Generating output files
add_custom_command(TARGET ${PROJECT_NAME}
    POST_BUILD
    COMMAND ${CMAKE_SYSTEM_NAME}size --format=sysv ${PROJECT_NAME} --radix=16
    COMMAND ${CMAKE_SYSTEM_NAME}size ${PROJECT_NAME}
    COMMAND ./scripts/postbuild.sh ${PROJECT_NAME}
    DEPENDS ${PROJECT_NAME}
)
