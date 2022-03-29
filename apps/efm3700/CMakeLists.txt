#
# CMake configuration
#
# Please refer to http://www.cmake.org/cmake/help/documentation.html
# You may also refer to http://www.cmake.org/cmake/help/syntax.html for a quick
# introduction to CMake's syntax.

cmake_minimum_required (VERSION 2.8)

# Name of the project
project (test_efm32)

# define some more paths to projects we depend on
set (MBED_SRC_PATH ${PROJECT_SOURCE_DIR}/../../mbed/mbed/libraries/mbed)
set (TOOLCHAIN_DIR ${PROJECT_SOURCE_DIR}/../../mbed/toolchain)

set (DEVICE_TYPE "EFM32GG990F1024")
set (TARGET_PLATFORM "TARGET_EFM32GG_STK3700")
set (TARGET_FAMILY "TARGET_EFM32")
set (PROGRAMMER "J_LINK") 
set (LINKER_FILE "${MBED_SRC_PATH}/targets/cmsis/TARGET_Silicon_Labs/TARGET_EFM32/${TARGET_PLATFORM}/TOOLCHAIN_GCC_ARM/efm32gg.ld")
set (START_FLASH_ADDR "0x00000000")

# It's best to hide all the details of setting up the variable SRCS in a CMake
# macro. The macro can then be called in all the project CMake list files to add
# sources.
#
# The macro first computes the path of the source file relative to the project
# root for each argument. If the macro is invoked from inside a project sub
# directory the new value of the variable SRCS needs to be propagated to the
# parent folder by using the PARENT_SCOPE option.
#
# Source: http://stackoverflow.com/questions/7046956/populating-srcs-from-cmakelists-txt-in-subdirectories
macro (add_sources)
    file (RELATIVE_PATH _relPath "${CMAKE_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}")
    foreach (_src ${ARGN})
        if (_relPath)
            list (APPEND SRCS "${_relPath}/${_src}")
        else()
            list (APPEND SRCS "${_src}")
        endif()
    endforeach()
    if (_relPath)
        # propagate to parent directory
        set (SRCS ${SRCS} PARENT_SCOPE)
    endif()
endmacro()

include(${TOOLCHAIN_DIR}/compiler.cmake)


############################################################################
# Build type should be clear from here so we
# can continue with selecting include directors, defines
# and other compiler/linker flags ...
############################################################################
# include directories
include_directories(
    ${MBED_SRC_PATH}/
    ${MBED_SRC_PATH}/api
    ${MBED_SRC_PATH}/common
    ${MBED_SRC_PATH}/hal
    ${MBED_SRC_PATH}/targets
    ${MBED_SRC_PATH}/targets/cmsis
    ${MBED_SRC_PATH}/targets/cmsis/TARGET_Silicon_Labs
    ${MBED_SRC_PATH}/targets/cmsis/TARGET_Silicon_Labs/TARGET_EFM32/${TARGET_PLATFORM}
    ${MBED_SRC_PATH}/targets/hal
    ${MBED_SRC_PATH}/targets/hal/TARGET_Silicon_Labs
    ${MBED_SRC_PATH}/targets/hal/TARGET_Silicon_Labs/TARGET_EFM32/emlib/inc    
    ${MBED_SRC_PATH}/targets/hal/TARGET_Silicon_Labs/TARGET_EFM32/${TARGET_PLATFORM}
    ${MBED_SRC_PATH}/targets/hal/TARGET_Silicon_Labs/TARGET_EFM32
)
include_directories(
    ${MBED_SRC_PATH}/targets/cmsis/TARGET_Silicon_Labs/TARGET_EFM32/${TARGET_PLATFORM}/TOOLCHAIN_GCC_ARM
)

# A macro to collect local sources into ${SRCS}.
# This variable gets propagated to the parent scope and is ultimately used in
# the top-level CMakeLists.txt to define the dependencies for the build target.
#
# Please note that files within this list are relative to the current folder.
# Please also note that this macro must be used at all CMakeLists.txt files at
# intermediate levels even if the list is empty--this is due to the Cmake magic
# involved in propagating variables to only the parent scope.
add_sources(
    main.cpp
)

# Use file globbing to collect all sources from external repositories. File-
# globbing is discouraged by CMake, except when collecting sources from an
# external source which remains mostly frozen. The risk with globbing is that
# CMake doesn't automatically update the makefiles if new sources are added to
# the globbed location.
#
file(GLOB MBED_SRC_SOURCES
    ${MBED_SRC_PATH}/common/*.c
    ${MBED_SRC_PATH}/common/*.cpp
    ${MBED_SRC_PATH}/targets/cmsis/TARGET_Silicon_Labs/TARGET_EFM32/${TARGET_PLATFORM}/*.c
    ${MBED_SRC_PATH}/targets/hal/TARGET_Silicon_Labs/TARGET_EFM32/${TARGET_PLATFORM}/*.c
    ${MBED_SRC_PATH}/targets/hal/TARGET_Silicon_Labs/TARGET_EFM32/*.c
    ${MBED_SRC_PATH}/targets/hal/TARGET_Silicon_Labs/TARGET_EFM32/emlib/src/*.c
)

add_sources(${MBED_SRC_SOURCES})

add_sources(
    ${MBED_SRC_PATH}/targets/cmsis/TARGET_Silicon_Labs/TARGET_EFM32/${TARGET_PLATFORM}/TOOLCHAIN_GCC_ARM/startup_efm32gg.S
)

############################################################################
# By now, we've traversed all subdirectories and have collected everything that
# needs to be built. We can define the build targets.
############################################################################
# add MbedTest as a build target depending on all the sources
add_executable(${CMAKE_PROJECT_NAME}.elf ${SRCS})

include(${TOOLCHAIN_DIR}/postbuild.cmake)
#add programmer commands
if(${PROGRAMMER} STREQUAL "ST_LINK")
    include(${TOOLCHAIN_DIR}/stlink.cmake)
else()
    include(${TOOLCHAIN_DIR}/jlink.cmake)
endif()


