########## Modules ##########
set(INCLUDES 
	${CMAKE_CURRENT_LIST_DIR}/GridEye
	${CMAKE_CURRENT_LIST_DIR}/SystemTime
    ${CMAKE_CURRENT_LIST_DIR}/SystemTick
    ${CMAKE_CURRENT_LIST_DIR}/SerialInterface
    ${CMAKE_CURRENT_LIST_DIR}/SramInterface
    ${CMAKE_CURRENT_LIST_DIR}/WIZnetInterface/DHCPClient
    ${CMAKE_CURRENT_LIST_DIR}/WIZnetInterface/DNSClient
    ${CMAKE_CURRENT_LIST_DIR}/WIZnetInterface/Socket
    ${CMAKE_CURRENT_LIST_DIR}/WIZnetInterface/WIZnet
    ${CMAKE_CURRENT_LIST_DIR}/WIZnetInterface
    ${CMAKE_CURRENT_LIST_DIR}/HTTPClient
    ${CMAKE_CURRENT_LIST_DIR}/HTTPClient/data
)

FILE(GLOB SOURCES
	${CMAKE_CURRENT_LIST_DIR}/GridEye/*.cpp
	${CMAKE_CURRENT_LIST_DIR}/SystemTime/*.cpp
	${CMAKE_CURRENT_LIST_DIR}/SystemTick/*.cpp
	${CMAKE_CURRENT_LIST_DIR}/SerialInterface/*.cpp
    ${CMAKE_CURRENT_LIST_DIR}/SramInterface/*.cpp
	${CMAKE_CURRENT_LIST_DIR}/WIZnetInterface/DHCPClient/*.cpp
    ${CMAKE_CURRENT_LIST_DIR}/WIZnetInterface/DNSClient/*.cpp
    ${CMAKE_CURRENT_LIST_DIR}/WIZnetInterface/Socket/*.cpp
    ${CMAKE_CURRENT_LIST_DIR}/WIZnetInterface/WIZnet/*.cpp
    ${CMAKE_CURRENT_LIST_DIR}/WIZnetInterface/*.cpp
    ${CMAKE_CURRENT_LIST_DIR}/HTTPClient/*.cpp
    ${CMAKE_CURRENT_LIST_DIR}/HTTPClient/data/*.cpp  	
)

########## Outputs ##########

# Add library
# add_library(drivers ${SOURCES})
# set(OPTIONAL_LIBS ${OPTIONAL_LIBS} drivers)

include_directories(${INCLUDES})
add_sources(${SOURCES})


# Add only headers as this isn't the base project
# set(DOC_FILES ${DOC_FILES} ${INCLUDES})
