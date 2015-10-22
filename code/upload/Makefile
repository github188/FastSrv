#last modify zengpw 2015-10-09
#author zengpw 2015-10-09

PROJECT_PATH = $(shell pwd)
PROJECT_NAME = upload
PROJECT_TYPE = BIN

SOURCE = $(wildcard *.c) $(wildcard *.cpp) $(wildcard *.cc)
SOURCE_INCLUDE = -I $(PROJECT_PATH) -I $(PROJECT_PATH)/../include -I $(ORACLE_SDK)
SOURCE_PATH = $(PROJECT_PATH)

LINK_LIB = -lcommon -lprotocol -lsession
LINK_LIB_PATH = -L $(PROJECT_PATH)/../lib

OUTPUT = $(PROJECT_PATH)/../bin
OUTPUT_TEMP = $(PROJECT_PATH)/../build_temp

#INSTALL_FILE = $(wildcard *.h)
#INSTALL_PATH = $(PROJECT_PATH)/../include/$(PROJECT_NAME)

include ../common.make