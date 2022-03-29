# mbed gcc/cmake toolchain

This repo contains the scripts to build the mbed source code and program the platform using jlink or st-link.

## Dependencies

Requires CMake, gcc arm toolchain, jlink and st-util.
For st-util, download and follow instructions from https://github.com/texane/stlink.
For jlink, download from the segger website, https://www.segger.com/jlink-software.html.

## Usage

Change the cmake to match the plaform. Start address for EFM32 is 0x00000000 and STM32 is 0x08000000. Current CMake targets the Giant Gecko STK3700.
