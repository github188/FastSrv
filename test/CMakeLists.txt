#instruction
#author:				zengpw
#last modify time:		2014年3月27日 17:01:59

#base cmake
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
INCLUDE(../base.cmake)

#code path
SET(PROJECT_SOURCE_DIR                  ${PS_HOME}/test)
SET(SERVER								${PROJECT_SOURCE_DIR}/as3_message.h ${PROJECT_SOURCE_DIR}/as3_server.cpp)
SET(CLIENT								${PROJECT_SOURCE_DIR}/as3_message.h ${PROJECT_SOURCE_DIR}/as3_client.cpp)

#link library
LINK_LIBRARIES(
ps_thread
ps_socket
ps_protocol
)

#output path
SET(PROJECT_BINARY_DIR          		${PROJECT_SOURCE_DIR}/build)
SET(EXECUTABLE_OUTPUT_PATH      		${PROJECT_SOURCE_DIR}/build/bin)
SET(LIBRARY_OUTPUT_PATH         		${PROJECT_SOURCE_DIR}/build/lib)

#output library
ADD_EXECUTABLE(as3_server ${SERVER})
ADD_EXECUTABLE(as3_client ${CLIENT})
INSTALL(TARGETS as3_server DESTINATION ${PS_BIN})
INSTALL(TARGETS as3_client DESTINATION ${PS_BIN})


