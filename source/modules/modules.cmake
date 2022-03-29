########## Modules ##########
set(INCLUDES 
	${CMAKE_CURRENT_LIST_DIR}/Tracker
	${CMAKE_CURRENT_LIST_DIR}/CommandParser
	${CMAKE_CURRENT_LIST_DIR}/Network
	${CMAKE_CURRENT_LIST_DIR}/AppTimer
	${CMAKE_CURRENT_LIST_DIR}/AppState
	${CMAKE_CURRENT_LIST_DIR}/AppFSM
	${CMAKE_CURRENT_LIST_DIR}/Settings
	${CMAKE_CURRENT_LIST_DIR}/Controller
)

FILE(GLOB SOURCES
	${CMAKE_CURRENT_LIST_DIR}/Tracker/*.cpp
	${CMAKE_CURRENT_LIST_DIR}/AppTimer/*.cpp
	${CMAKE_CURRENT_LIST_DIR}/AppState/*.cpp
	${CMAKE_CURRENT_LIST_DIR}/AppFSM/*.cpp
	${CMAKE_CURRENT_LIST_DIR}/Network/*.cpp
	${CMAKE_CURRENT_LIST_DIR}/CommandParser/*.cpp
	${CMAKE_CURRENT_LIST_DIR}/Settings/*.cpp
	${CMAKE_CURRENT_LIST_DIR}/Controller/*.cpp
)

########## Outputs ##########

# Add library
# add_library(drivers ${SOURCES})
# set(OPTIONAL_LIBS ${OPTIONAL_LIBS} drivers)

include_directories(${INCLUDES})
add_sources(${SOURCES})


# Add only headers as this isn't the base project
# set(DOC_FILES ${DOC_FILES} ${INCLUDES})
