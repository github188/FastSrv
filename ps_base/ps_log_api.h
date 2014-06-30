#ifndef _PS_LOG_API_H_
#define _PS_LOG_API_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <pthread.h>
#include <sys/time.h>
#include <sys/types.h>


#define MAX_NUMBER 20

#define MAX_LENGTH 1024

#define DEBUG_LEVEL	 0
#define INFO_LEVEL	 1
#define WARN_LEVEL   2
#define SEVERE_LEVEL 3
#define FATAL_LEVEL  4


extern int	iToLog;
extern int	iToConsoleLog;
extern int	iLogLevel;

int LogInit(const char* cfgFile,const  char* modName,const char* ext);
int logInit( const char* cfgfile, const char* modName);
int LogAppend (int logLevel,const char*  logMsg, ...); 

int LogInitAll(const char* modName,const char* logFileName, int level, int logOn, int consoleOn);

int LogSetConsoleOn (int consoleOn);
int LogSetLogOn (int logOn);
int LogSetLevel (int level);
int LogSetFileName (char *logFileName);
int LogSetModName (const char *modName);

int LogTruncate (char *logFileName);

#endif
