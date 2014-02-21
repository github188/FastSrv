#!/bin/sh
echo "\n\t\t\t\t=============================cmake使用============================="
echo "\n\t\t\t\t=========Ⅰ.在本目录下执行 \"cmake ./\"，生成 Makefile 文件========"
echo "\n\t\t\t\t=========Ⅱ.执行\"gmake\"，编译===================================="
echo "\n\t\t\t\t=========Ⅲ.清理直接执行本脚本即可================================="
echo "\n"
gmake clean
rm -rf CMakeCache.txt Makefile cmake_install.cmake CMakeFiles core*