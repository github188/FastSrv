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

#include "log.h"

namespace common
{
	Log* Log::lo = NULL;
	Logger Log::_loggerC = Logger::getInstance("_loggerC");
	Logger Log::_loggerD = Logger::getInstance("_loggerD");

	Log* Log::create(const char* fileWholePath)
	{
		if(lo == NULL)
		{
			lo = new Log;
			lo->logInit(fileWholePath);
		}

		return lo;
	}


	void Log::logInit(const char* fileWholePath)
	{
		string path(fileWholePath);
		path = path.substr(0, path.rfind('/'));
		cout << "log path = " << path;

		DIR* dr;
		if((dr = opendir(path.c_str())) == NULL)
		{
			cout << " not exist! " << endl;

			if(mkdir(path.c_str(), S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH) == 0)
				cout << "create log dir " << path << " success! " << endl;
			else
				cout << "create log dir " << path << " fail! " << endl;
		}
		else
		{
			cout << endl;
			closedir(dr);
		}

		auto_ptr<Layout> _layoutC(new PatternLayout("%D{%Y/%m/%d %H:%M:%S} %t [%p] %m [%l]%n"));
		SharedObjectPtr<Appender> _appendC(new ConsoleAppender());
		_appendC->setName("Append_Console");
		_appendC->setLayout(_layoutC);
		_loggerC.addAppender(_appendC);
		_loggerC.setLogLevel(ALL_LOG_LEVEL);

		auto_ptr<Layout> _layoutD(new PatternLayout("%D{%Y/%m/%d %H:%M:%S} %t [%p] %m [%l]%n"));
		SharedObjectPtr<Appender> _appendD(new DailyRollingFileAppender(fileWholePath, HOURLY, true, 1));
		_appendD->setName("Append_DailyRollingFile");
		_appendD->setLayout(_layoutD);
		_loggerD.addAppender(_appendD);
		_loggerD.setLogLevel(ALL_LOG_LEVEL);
	}
};// namespace common