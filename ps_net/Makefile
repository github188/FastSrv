##################################################################################
#在 Linux/Unix/AIX 等系统上进行编译需要的Makefile文件
#
#变量说明：
#
#	参考所引用的 common.make 文件
#	Makefile 的 include 模式为原地展开，所以 include 要放到 Makefile 的最下面
#
#使用说明：
#
#	all/install/clean/check
#
#修订历史：
#
#	zengpw		2014.07.07 创建文件
#	zengpw		2014.07.08 修改 common.make 和 Makefile ，完成基础编译功能
#
#
##################################################################################

#安装头文件时需要用到 PROJECT_NAME
PROJECT_NAME = ps_framework

#目标类型
DEST = SO

#目标
TARGET_X = libpsframework.so

#需要安装的文件，暂定为安装所有.h
TARGET_INSTALL = $(wildcard *.h)

#include 必须放在最下面
include ../ps_public/common.make


