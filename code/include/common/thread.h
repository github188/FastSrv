/*
//
//	Last Modify Date: 2015-11-06
//	Author: zengpw
//	History:
//					2015-08-27 zengpw created
//	File Property: public
//	Future:
//					I. 线程
//
//
*/

#ifndef _COMMON_THREAD_H_
#define _COMMON_THREAD_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <pthread.h>
#include <unistd.h>
#include "log.h"

using namespace std;

namespace common
{
	typedef struct SThread
	{
		pthread_t pid;
		void* exit;
	}SThread;
	typedef vector<SThread> SThreadVec;

	class Thread
	{
	public:
		int create(void* (*start_rtn)(void*), void* arg);
		int join();
		int stop();
	public:
		bool work;
		SThreadVec vecSThread;
	};// class Thread
};// namespace common

#endif