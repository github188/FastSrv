#last modify zengpw 2015-09-18
#author zengpw 2015-08-05

OS := $(shell uname -s)

ifeq "$(OS)" "Linux"
	include ../linux.make
endif