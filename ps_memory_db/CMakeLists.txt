#instruction
#author:				zengpw
#last modify time:		2014年5月7日 21:16:01

#base cmake
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
INCLUDE(../base.cmake)

#code path
SET(PROJECT_SOURCE_DIR                  ${PS_HOME}/ps_memory_db)
FILE(GLOB SOURCE						${PROJECT_SOURCE_DIR} *)
MESSAGE(STATUS ${CMAKE_DEBUG}"the source is : "${SOURCE})

#output path
SET(PROJECT_BINARY_DIR          		${PROJECT_SOURCE_DIR}/build)
SET(EXECUTABLE_OUTPUT_PATH      		${PROJECT_SOURCE_DIR}/build/bin)
SET(LIBRARY_OUTPUT_PATH         		${PROJECT_SOURCE_DIR}/build/lib)

#output library
ADD_LIBRARY(ps_memory_db SHARED ${SOURCE})
INSTALL(TARGETS ps_memory_db LIBRARY DESTINATION ${PS_LIB})
INSTALL(FILES ps_memory_db_api.h DESTINATION ${PS_PUBLIC})


