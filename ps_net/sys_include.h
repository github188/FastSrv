#ifndef __PS_NET_COMMON_INCLUDE__
#define __PS_NET_COMMON_INCLUDE__
//////////////////////////////////////////////////////////////////////////
//
//	Creater : zengpw
//	Create Date : 2014年8月21日
//	Modify history :
//					2014年8月21日 zengpw 重新设计
//	File Property : private （此头文件是私有的）
//	Description : 包含的系统头文件
//
//////////////////////////////////////////////////////////////////////////

/* c_c++ */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

#ifdef __GNU_C__
/* linux */
#include <stdint.h>
#include <errno.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/types.h>
#endif //__GNU_C__

#endif //__PS_NET_COMMON_INCLUDE__
