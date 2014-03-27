#instruction
#author:				zengpw
#last modify time:		2014年3月27日 17:01:59

#base cmake
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
INCLUDE(../base.cmake)

#code path
SET(PROJECT_SOURCE_DIR                  ${PS_HOME}/test)
SET(SERVER								${PROJECT_SOURCE_DIR}/message.h ${PROJECT_SOURCE_DIR}/server.cpp)
SET(CLIENT								${PROJECT_SOURCE_DIR}/message.h ${PROJECT_SOURCE_DIR}/client.cpp)
MESSAGE(STATUS ${CMAKE_DEBUG}"the source is : "${SOURCE})

#link library
LINK_LIBRARIES(
ps_thread
ps_socket
)

#output path
SET(PROJECT_BINARY_DIR          		${PROJECT_SOURCE_DIR}/build)
SET(EXECUTABLE_OUTPUT_PATH      		${PROJECT_SOURCE_DIR}/build/bin)
SET(LIBRARY_OUTPUT_PATH         		${PROJECT_SOURCE_DIR}/build/lib)

#output library
ADD_EXECUTABLE(server ${SERVER})
ADD_EXECUTABLE(client ${CLIENT})
INSTALL(TARGETS server DESTINATION ${PS_BIN})
INSTALL(TARGETS client DESTINATION ${PS_BIN})


