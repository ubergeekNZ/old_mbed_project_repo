set(CMAKE_CXX_COMPILER arm-none-eabi-g++)
set(CMAKE_C_COMPILER   arm-none-eabi-gcc)
set(SIZE_COMMAND       arm-none-eabi-size)
set(OBJCOPY_COMMAND    arm-none-eabi-objcopy)
set(OBJDUMP_COMMAND    arm-none-eabi-objdump)


set(MAIN_TARGET        ${PROJECT_NAME}.elf)
enable_language(ASM)

message(STATUS "C compiler  : ${CMAKE_C_COMPILER}")
message(STATUS "C++ compiler: ${CMAKE_CXX_COMPILER}")
message(STATUS "Size command: ${SIZE_COMMAND}")
message(STATUS "Main target : ${MAIN_TARGET}")

# Generic compiler flags
add_definitions(
    -O0
    -g3
    -D${TARGET_PLATFORM}
    -DTARGET_M4
    -D${TARGET_FAMILY}
    -D__CORTEX_M4
    -DARM_MATH_CM4
    -D__MBED__=1
    -DMBED_BUILD_TIMESTAMP=1399904910.34
    -D${DEVICE_TYPE}
)


add_definitions(
    -mcpu=cortex-m4
    -mthumb
    -Wall
    -Wextra
    -Wno-unused-parameter
    -Wno-missing-field-initializers
    -Wno-error=switch
    -Wno-switch
    -Wa,-adhlns=$@.lst
    -fmessage-length=0
    -fno-builtin
    -ffunction-sections
    -fdata-sections
    -fno-delete-null-pointer-checks
    -fomit-frame-pointer
    -fno-common
    -funsigned-bitfields
    -DTOOLCHAIN_GCC_ARM
    -DTOOLCHAIN_GCC
)

# Language specifc compiler flags.
set(CMAKE_CXX_FLAGS
    "${CMAKE_CXX_FLAGS} -std=gnu++98 -fno-rtti -fno-exceptions -fno-threadsafe-statics")
set(CMAKE_C_FLAGS
    "${CMAKE_C_FLAGS} -std=gnu99 -Wno-pointer-sign -Wno-pointer-to-int-cast")
set(CMAKE_ASM_FLAGS
    "${COMMON_COMPILE_FLAGS} -x assembler-with-cpp")

SET(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS
    -T${LINKER_FILE})
SET(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS
    "${CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS} -Wl,--gc-sections -Wl,--wrap,main -Wl,-Map=${PROJECT_NAME}.map -mcpu=cortex-m4 -mthumb --specs=nano.specs -lstdc++ -lsupc++ -lm -lc -lgcc -lnosys -lstdc++ -lsupc++ -lm -lc -lgcc -lnosys")
