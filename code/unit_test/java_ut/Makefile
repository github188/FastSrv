#last modify zengpw 2015-11-05
#author zengpw 2015-10-29

PROJECT_PATH = $(shell pwd)
PROJECT_NAME = java_ut
PROJECT_TYPE = BIN

SOURCE = $(wildcard *.c) $(wildcard *.cpp) $(wildcard *.cc)
SOURCE_INCLUDE = -I $(PROJECT_PATH) -I $(PROJECT_PATH)/../../include -I $(ORACLE_SDK) -I $(ICE_HOME)/include
SOURCE_PATH = $(PROJECT_PATH)

LINK_LIB = -lcommon -lprotocol -lsession -lIce -lIceUtil
LINK_LIB_PATH = -L $(PROJECT_PATH)/../../lib -L $(ICE_HOME)/lib64

OUTPUT = $(PROJECT_PATH)/../../bin
OUTPUT_TEMP = $(PROJECT_PATH)/../../build_temp

#INSTALL_FILE = $(wildcard *.h)
#INSTALL_PATH = $(PROJECT_PATH)/../include/$(PROJECT_NAME)

include ../../linux.make