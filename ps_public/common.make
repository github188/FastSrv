##################################################################################
#在 Linux/Unix/AIX 等系统上进行编译的makefile预定义头文件，包括变量的推导
#
#变量说明：
#
#	CXX					C++编译器
#	CXX_FLAGS			C++编译器的选项
#	PROJECT_DIR			工程目录
#	BUILD_DIR			编译目录
#	INSTALL_DIR			输出目录
#	TARGET				源文件，如果没有定义，默认为 project 目录下所有 .cpp 文件
#	INCLUDE_PATH		头文件路径
#	ADD_LIB				附加的库
#	ADD_LIB_PATH		附加的库的路径
#	DEST				输出目标类型： SO或BIN
#
#修订历史：
#
#	zengpw		2014.07.07 创建文件，仅仅适配 Ubuntu 14.04 x64
#
#
##################################################################################

#编译器
CXX = g++
CXX_FLAGS = -g -O3 -fpic -ftemplate-depth-64 -m64

#编译环境
PROJECT_DIR = $(shell pwd)
BUILD_DIR = $(PROJECT_DIR)/build
INSTALL_DIR ?= $(PROJECT_DIR)/../output

TARGET ?= $(wildcard *.cpp)
INCLUDE_PATH += -I $(PROJECT_DIR) -I $(INSTALL_DIR)
ADD_LIB += -l pthread
ADD_LIB_PATH += /usr/local/lib
DEST ?= BIN

#推导变量
ifeq "$(DEST)" "SO"
	CXX_FLAGS += -shared
endif

#构建各种 target
.PHONY: all install check

check:
	@echo ""
	@echo "    Hello beautiful world!"
	@echo "    我们的 Makefile 尚未完工，因此您只能看到部分信息。/ Our Makefile is not complete"
	@echo ""
	@echo "    目前仅仅适配 Ubuntu 14.04 x64 ，create by zengpw , have fun! last modify time : 2014.07.07 "
	@echo "    C++编译器： "$(CXX)
	@echo "    C++编译器选项： "$(CXX_FLAGS)	
	@echo "    工程目录 ： "$(PROJECT_DIR)
	@echo "    编译目录 ： "$(BUILD_DIR)
	@echo "    输出目录 ： "$(INSTALL_DIR)
	@echo "    源文件 ："$(TARGET)
	@echo "    头文件路径 ： "$(INCLUDE_PATH)
	@echo "    附加库 ： "$(ADD_LIB)
	@echo "    附加库路径 ： "$(ADD_LIB_PATH)
	@echo "    输出目标类型 ： "$(DEST)
	@echo ""

all:$(TARGET)
	$(TARGET): %.o: %.cpp
	$(CXX) $(CXX_FLAGS) $(INCLUDE_PATH) -c $< -o $(BUILD_DIR)/$@ $(ADD_LIB_PATH) $(ADD_LIB)

install:
	@if [ ! -d $(INSTALL_DIR) ]; then $(MKDIR) -p $(INSTALL_DIR); fi;





