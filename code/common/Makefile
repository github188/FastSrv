#last modify zengpw 2015-10-23
#author zengpw 2015-08-07

PROJECT_PATH = $(shell pwd)
PROJECT_NAME = common
PROJECT_TYPE = SO

SOURCE = $(wildcard *.c) $(wildcard *.cpp) $(wildcard *.cc)
SOURCE_INCLUDE = -I $(PROJECT_PATH) -I $(PROJECT_PATH)/../include/common -I $(PROJECT_PATH)/../include -I $(ORACLE_SDK) -I /usr/local/include/python3.3m
SOURCE_PATH = $(PROJECT_PATH)

LINK_LIB = -levent -lpthread -lhiredis -llog4cplus -locci -lclntsh -lpython3 -lpython3.3m
LINK_LIB_PATH = -L $(PROJECT_PATH)/../lib -L $(ORACLE_LIB)

OUTPUT = $(PROJECT_PATH)/../lib
OUTPUT_TEMP = $(PROJECT_PATH)/../build_temp

INSTALL_FILE = $(wildcard *.py)
INSTALL_PATH = $(PROJECT_PATH)/../bin

include ../common.make