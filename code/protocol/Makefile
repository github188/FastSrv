#last modify zengpw 2015-08-07
#author zengpw 2015-08-07

PROJECT_PATH = $(shell pwd)
PROJECT_NAME = protocol
PROJECT_TYPE = SO

SOURCE = $(wildcard *.c) $(wildcard *.cpp) $(wildcard *.cc)
SOURCE_INCLUDE = -I $(PROJECT_PATH) -I $(PROJECT_PATH)/../include/protocol -I $(PROJECT_PATH)/../include
SOURCE_PATH = $(PROJECT_PATH)

LINK_LIB = -lprotoc -lprotobuf -lprotobuf-lite -lcommon
LINK_LIB_PATH = -L $(PROJECT_PATH)/../lib

OUTPUT = $(PROJECT_PATH)/../lib
OUTPUT_TEMP = $(PROJECT_PATH)/../build_temp

#INSTALL_FILE = $(wildcard *.h)
#INSTALL_PATH = $(PROJECT_PATH)/../include/$(PROJECT_NAME)

include ../common.make