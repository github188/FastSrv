#cmake version
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

#project name
PROJECT(PURE_SERVER)

#set environment variable
SET(HOME /home/zengpw/work/pure_server)
SET(SRC_LIST
${HOME}/ps_task.hpp
${HOME}/ps_thread.hpp
${HOME}/ps_thread_pool.hpp
${HOME}/ps_socket_tcp.hpp
${HOME}/test/main.cpp
)

#execute path
ADD_EXECUTABLE(pure_server ${SRC_LIST})

