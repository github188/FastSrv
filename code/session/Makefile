#last modify zengpw 2015-09-16
#author zengpw 2015-09-16

PROJECT_PATH = $(shell pwd)
PROJECT_NAME = session
PROJECT_TYPE = SO

SOURCE = $(wildcard *.c) $(wildcard *.cpp) $(wildcard *.cc)
SOURCE_INCLUDE = -I $(PROJECT_PATH) -I $(PROJECT_PATH)/../include/session -I $(PROJECT_PATH)/../include -I $(ORACLE_SDK)
SOURCE_PATH = $(PROJECT_PATH)

LINK_LIB = -lcommon -lprotocol
LINK_LIB_PATH = -L $(PROJECT_PATH)/../lib

OUTPUT = $(PROJECT_PATH)/../lib
OUTPUT_TEMP = $(PROJECT_PATH)/../build_temp

#INSTALL_FILE = $(wildcard *.h)
#INSTALL_PATH = $(PROJECT_PATH)/../include/$(PROJECT_NAME)

include ../common.make