#instruction
#author:				zengpw
#last modify time:		2014年4月21日 11:27:20

#cmake version
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
SET(CMAKE_DEBUG "                 ====ZENGPW CMAKE DEBUG INFO====                 ")

#project set
PROJECT(PURE_SERVER)
SET(PS_HOME                     /home/zengpw/work/pure_server)
SET(PS_PUBLIC					${PS_HOME}/ps_public)
SET(PS_LIB						${PS_HOME}/lib)
SET(PS_BIN						${PS_HOME}/bin)

#include path
INCLUDE_DIRECTORIES(
.
${PS_PUBLIC}
)

#link path
LINK_DIRECTORIES(
/usr/lib
/usr/local/lib
${PS_LIB}
)

#compile option
SET(CMAKE_BUILE_TYPE DEBUG)
SET(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror -Wconversion -Wshadow -D_REENTARNT -O2 -g -std=gnu++0x")

MESSAGE(STATUS ${CMAKE_DEBUG}" base.cmake loading finish! ")

