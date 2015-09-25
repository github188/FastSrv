#author zengpw 2015-08-05
#last modify zengpw 2015-09-18

OS := $(shell uname -s)

ifeq "$(OS)" "Linux"
	include ../linux.make
endif