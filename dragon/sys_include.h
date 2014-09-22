#ifndef __DRAGON_SYS_INCLUDE__
#define __DRAGON_SYS_INCLUDE__
//////////////////////////////////////////////////////////////////////////
//
//	Creater : zengpw
//	Create Date : 2014年9月2日
//	Modify history :
//					2014年9月2日 zengpw 创建文件
//	File Property : private
//	Description :
//					I. 包含的系统头文件
//
//////////////////////////////////////////////////////////////////////////

/* c_c++ */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <iostream>

/* stl */
#include <list>
#include <map>

#ifdef __GNU_C__
/* linux */
#include <stdint.h>
#include <errno.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/types.h>
#endif //__GNU_C__

#endif //__DRAGON_SYS_INCLUDE__
