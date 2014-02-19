#cmake version
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

#project name
PROJECT(PURE_SERVER)

#set environment variable
SET(HOME /home/zengpw/work/pure_server)
SET(CMAKE_CXX_FLAGS "-Wall -D_REENTARNT -O2 -g -std=gnu++0x")

#execute path
SET(SRC_LIST ${HOME}/example/ps_server.cpp)
ADD_EXECUTABLE(pure_server ${SRC_LIST})

SET(SRC_LIST ${HOME}/example/ps_client.cpp)
ADD_EXECUTABLE(client ${SRC_LIST})

