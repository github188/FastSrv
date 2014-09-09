#ifndef __PS_FW_SYS_INCLUDE__
#define __PS_FW_SYS_INCLUDE__
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
#include <assert.h>
#include <stdarg.h>

/* stl */
#include <list>
#include <map>

#ifdef _MSC_VER
#include "pthread.h"
#endif //_MSC_VER

#ifdef __GNU_C__
#include <pthread.h>
#endif //__GNU_C__

#ifdef _MSC_VER
/* win socket */
#include <WinSock2.h>
#endif //_MSC_VER

#ifdef __GNU_C__
/* linux */
#include <stdint.h>
#include <errno.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/types.h>
/* linux socket */
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/select.h>
#endif //__GNU_C__

#endif //__PS_FW_SYS_INCLUDE__
