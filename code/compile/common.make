#author zengpw 2015-08-05
#last modify zengpw 2015-08-05

OS := $(shell uname -s)

ifeq "$(OS)" "Linux"
	include ../compile/linux.make
endif