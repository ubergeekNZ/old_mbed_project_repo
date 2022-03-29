# Add a custom target to generate the .hex and .bin files using objcopy, and output them to the Output directory
ADD_CUSTOM_COMMAND(TARGET ${CMAKE_PROJECT_NAME}.elf 
	POST_BUILD COMMAND 
	${SIZE_COMMAND} ARGS ${CMAKE_PROJECT_NAME}.elf)

ADD_CUSTOM_COMMAND(TARGET ${CMAKE_PROJECT_NAME}.elf
    POST_BUILD COMMAND
    ${OBJCOPY_COMMAND} -O binary ${CMAKE_PROJECT_NAME}.elf ${CMAKE_PROJECT_NAME}.bin 2>/dev/null
)

ADD_CUSTOM_COMMAND(TARGET ${CMAKE_PROJECT_NAME}.elf
    POST_BUILD COMMAND
    ${OBJCOPY_COMMAND} -O ihex ${CMAKE_PROJECT_NAME}.elf ${CMAKE_PROJECT_NAME}.hex 2>/dev/null
)
