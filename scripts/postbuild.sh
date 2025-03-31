#!/bin/sh

echo "Generating output: binary & hex files:"
TARGET_FILE_NAME=`echo $1 | cut -d'.' -f1`
COMPILER_PREFIX=arm-none-eabi-
IMAGES_DIR=./images
BUILD_DIR=./
APP_EXE_NAME=${TARGET_FILE_NAME}
APP_BIN_NAME=${APP_EXE_NAME}
APP_HEX_NAME=${APP_EXE_NAME}

echo ${APP_HEX_NAME}.bin
echo ${APP_BIN_NAME}.hex

if [ ! -d ${IMAGES_DIR} ] ; then
    mkdir ${IMAGES_DIR}
fi

cd ${IMAGES_DIR}
pwd
rm *.bin *.hex 2>/dev/null
${COMPILER_PREFIX}objcopy -O ihex ../${APP_EXE_NAME}.elf ./${APP_HEX_NAME}.hex
${COMPILER_PREFIX}objcopy -O binary ../${APP_EXE_NAME}.elf ./${APP_BIN_NAME}.bin
