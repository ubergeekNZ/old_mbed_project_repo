SET(DEBUG_PORT "4242")


SET(GDB_SPEED_STRING "#monitor speed 8000 #command not supported for stlink")
SET(GDB_FLASH_STRING "#monitor flash device ${DEVICE} #command not supported for stlink")

CONFIGURE_FILE(${CMAKE_CURRENT_LIST_DIR}/gdbcommands.txt ${CMAKE_CURRENT_BINARY_DIR}/gdbcommands.txt)

ADD_CUSTOM_TARGET(debug DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_PROJECT_NAME}.elf COMMAND arm-none-eabi-gdb --tui --se=${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_PROJECT_NAME}.elf --command=${CMAKE_CURRENT_BINARY_DIR}/gdbcommands.txt)
ADD_CUSTOM_TARGET(debug-server COMMAND st-util :${DEBUG_PORT})

#Depend on elf but use .bin for flash as build doesn't know .bin depends on elf.
ADD_CUSTOM_TARGET(flash DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_PROJECT_NAME}.elf COMMAND stdbuf -oL st-flash --reset write ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_PROJECT_NAME}.bin ${START_FLASH_ADDR} 2>1 )
ADD_CUSTOM_TARGET(erase COMMAND stdbuf -oL st-flash erase)

ADD_CUSTOM_TARGET(reset DEPENDS COMMAND JLinkExe -device ${DEVICE_TYPE} -CommanderScript ${CMAKE_CURRENT_LIST_DIR}/resetcommands.txt)

add_custom_target(clean-all rm -rf *)