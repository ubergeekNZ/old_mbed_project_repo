########## Modules ##########
set(INCLUDES 
	${CMAKE_CURRENT_LIST_DIR}/drivers
	${CMAKE_CURRENT_LIST_DIR}/modules
	${CMAKE_CURRENT_LIST_DIR}/common
)

# Set sources
# FILE(GLOB SOURCES
# 	${CMAKE_CURRENT_LIST_DIR}/*.cpp
# )

########## Outputs ##########

# # Add library
# add_library(interfaces ${SOURCES})
# set(OPTIONAL_LIBS ${OPTIONAL_LIBS} interfaces)

include_directories(${INCLUDES})


# Add only headers as this isn't the base project
set(DOC_FILES ${DOC_FILES} ${INCLUDES})
