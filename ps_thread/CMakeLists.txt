#instruction
#author:				zengpw
#last modify time:		2014年4月22日 16:44:13

#base cmake
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
INCLUDE(../base.cmake)

#code path
SET(PROJECT_SOURCE_DIR                  ${PS_HOME}/ps_thread)
FILE(GLOB SOURCE						${PROJECT_SOURCE_DIR} *)
MESSAGE(STATUS ${CMAKE_DEBUG}"the source is : "${SOURCE})

#link library
LINK_LIBRARIES(
pthread
ps_thread_queue
)

#output path
SET(PROJECT_BINARY_DIR          		${PROJECT_SOURCE_DIR}/build)
SET(EXECUTABLE_OUTPUT_PATH      		${PROJECT_SOURCE_DIR}/build/bin)
SET(LIBRARY_OUTPUT_PATH         		${PROJECT_SOURCE_DIR}/build/lib)

#output library
ADD_LIBRARY(ps_thread SHARED ${SOURCE})
INSTALL(TARGETS ps_thread LIBRARY DESTINATION ${PS_LIB})
INSTALL(FILES ps_thread_api.h DESTINATION ${PS_PUBLIC})


