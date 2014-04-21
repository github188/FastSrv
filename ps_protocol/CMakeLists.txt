#instruction
#author:				zengpw
#last modify time:		2014年4月21日 11:09:11

#base cmake
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
INCLUDE(../base.cmake)

#code path
SET(PROJECT_SOURCE_DIR                  ${PS_HOME}/ps_protocol)
SET(AS3									${PROJECT_SOURCE_DIR}/ps_protocol_as3_api.h ${PROJECT_SOURCE_DIR}/ps_protocol_as3.cpp)

#link library
LINK_LIBRARIES(
ps_socket
)

#output path
SET(PROJECT_BINARY_DIR          		${PROJECT_SOURCE_DIR}/build)
SET(EXECUTABLE_OUTPUT_PATH      		${PROJECT_SOURCE_DIR}/build/bin)
SET(LIBRARY_OUTPUT_PATH         		${PROJECT_SOURCE_DIR}/build/lib)

#output library
ADD_LIBRARY(ps_protocol SHARED ${AS3})
INSTALL(TARGETS ps_protocol LIBRARY DESTINATION ${PS_LIB})
INSTALL(FILES ps_protocol_as3_api.h DESTINATION ${PS_PUBLIC})


