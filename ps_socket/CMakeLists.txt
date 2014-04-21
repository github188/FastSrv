#instruction
#author:				zengpw
#last modify time:		2014年3月27日 17:01:59

#base cmake
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
INCLUDE(../base.cmake)

#code path
SET(PROJECT_SOURCE_DIR                  ${PS_HOME}/ps_socket)
FILE(GLOB SOURCE						${PROJECT_SOURCE_DIR} *)
MESSAGE(STATUS ${CMAKE_DEBUG}"the source is : "${SOURCE})

#link library
LINK_LIBRARIES(
ps_thread
)

#output path
SET(PROJECT_BINARY_DIR          		${PROJECT_SOURCE_DIR}/build)
SET(EXECUTABLE_OUTPUT_PATH      		${PROJECT_SOURCE_DIR}/build/bin)
SET(LIBRARY_OUTPUT_PATH         		${PROJECT_SOURCE_DIR}/build/lib)

#output library
ADD_LIBRARY(ps_socket SHARED ${SOURCE})
INSTALL(TARGETS ps_socket LIBRARY DESTINATION ${PS_LIB})
INSTALL(FILES ps_socket_api.h DESTINATION ${PS_PUBLIC})


