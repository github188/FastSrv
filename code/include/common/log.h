/*
//
//	Last Modify Date: 2015-12-25
//	Author: zengpw
//	History:
//					2015-09-21 zengpw created
//	File Property: public
//	Future:
//					I. 封装 log4cplus
//
//
*/

#ifndef _COMMON_LOG_H_
#define _COMMON_LOG_H_

#include <iostream>
#include <string>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>
#include "log4cplus/layout.h"
#include "log4cplus/fileappender.h"
#include "log4cplus/consoleappender.h"
#include "log4cplus/loggingmacros.h"
#include "log4cplus/logger.h"
#include "macro.h"

using namespace std;
using namespace log4cplus;
using namespace log4cplus::helpers;

#define LOG_TRACE(p) LOG4CPLUS_TRACE(common::Log::_loggerC, p);	\
					LOG4CPLUS_TRACE(common::Log::_loggerD, p)
#define LOG_DEBUG(p) LOG4CPLUS_DEBUG(common::Log::_loggerC, p);	\
					LOG4CPLUS_DEBUG(common::Log::_loggerD, p)
#define LOG_INFO(p) LOG4CPLUS_INFO(common::Log::_loggerC, p);	\
					LOG4CPLUS_INFO(common::Log::_loggerD, p)
#define LOG_WARN(p) LOG4CPLUS_WARN(common::Log::_loggerC, p);	\
					LOG4CPLUS_WARN(common::Log::_loggerD, p)
#define LOG_ERROR(p) LOG4CPLUS_ERROR(common::Log::_loggerC, p);	\
					LOG4CPLUS_ERROR(common::Log::_loggerD, p)


namespace common
{
	class Log
	{
	public:
		static Logger _loggerC;
		static Logger _loggerD;
		void logInit(const char* fileWholePath);
	public:
		static Log* create(const char* fileWholePath);
	private:
		static Log* lo;
	private:
		Log(){}
	};
};// namespace common

#endif