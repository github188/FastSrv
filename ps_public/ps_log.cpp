#include <stdarg.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include "ps_log_api.h"

#define RW_MULTI_THREAD 1

#define DEBUG_LEVEL	 0
#define INFO_LEVEL	 1
#define WARN_LEVEL   2
#define SEVERE_LEVEL 3
#define FATAL_LEVEL  4
#define FALSE -1
#define TRUE  1


static pthread_mutex_t g_logMutex;


int iToConsoleLog = 0;
int iToLog = 0;
static char nullResult[]="";
static char strLogFileName[128];;
static char strModName[128];
char strLogLevel[10];

int iLogLevel;


/*读配置文件实现 初始化 待实现*/
int logInit( const char* cfgfile, const char* modName)
{
		
			char cfgFile[128],logModName[32];
			char logfile[128], loglevel[16], logon[8], consoleon[8];
			int log_level, log_on=1, console_on=1;

			#ifdef RW_MULTI_THREAD
				pthread_mutex_init(&g_logMutex, NULL);
			#endif
/*
			strcpy(cfgFile, cfgfile);
			sprintf(logModName,"[%s]",modName);
	
			if (init_config(cfgFile)== FALSE)
			{
				printf("can not access the file %s\n",cfgFile);
				return FALSE;
			}

      if( get_config(logModName,"logFile", logfile) )
      {
              printf( "logFile is not set in %s \n " ,cfgFile );
              return FALSE;
      }

      if( get_config(logModName,"logLevel", loglevel) )
      {
              printf( "logLevel is not set in %s \n " ,cfgFile );
              return FALSE;
      }

      if( strcmp(loglevel ,"FATAL_LEVEL") == 0 )
              log_level = FATAL_LEVEL;
      else if( strcmp(loglevel ,"SEVERE_LEVEL") == 0 )
              log_level = SEVERE_LEVEL;
      else if( strcmp(loglevel ,"WARN_LEVEL") == 0 )
              log_level = WARN_LEVEL;
      else if( strcmp(loglevel ,"INFO_LEVEL") == 0 )
              log_level = INFO_LEVEL;
      else if( strcmp(loglevel ,"DEBUG_LEVEL") == 0 )
              log_level = DEBUG_LEVEL;
      else
      {
              printf(  "no such [log] level defined \n" );
              return -1;
      }

      if( get_config(logModName,"logOn", logon) )
      {
              printf( "logOn is not set in %s \n " ,cfgFile );
              return FALSE;
      }
      if( strcmp(logon ,"FALSE") == 0 )
      {
              log_on = FALSE;
      }

      if( get_config(logModName,"consoleOn", consoleon) )
      {
              printf( "consoleOn is not set in %s \n" ,cfgFile );
              return FALSE;
      }
      if( strcmp(consoleon ,"FALSE") == 0 )
      {
              console_on = FALSE;
      }


      }
*/      
      return(LogInitAll(modName,logfile,log_level,log_on, console_on));
}


int LogInit( const char* cfgfile, const char* modName,const char* filename,char* level,int logOn, int consoleOn)
{

			int log_level;

			#ifdef RW_MULTI_THREAD
				pthread_mutex_init(&g_logMutex, NULL);
			#endif

      log_level  = strcmp(level,"DEBUG_LEVEL")==0?0:strcmp(level,"INFO_LEVEL")==0?1:strcmp(level,"WARN_LEVEL")==0?2:strcmp(level,"SEVERE_LEVEL")==0?3:strcmp(level,"FATAL_LEVEL")==0?4:-1;

      if(log_level<0)
      {
              printf(  "no such [log] level defined \n" );
              return -1;
      }
      strcpy(strLogLevel,level);
      return(LogInitAll(modName,filename,log_level,logOn, consoleOn));
}

int LogInitAll(const char* modname, const char* filename,int level,int logOn, int consoleOn)
{
			if( !LogSetModName(modname) )
				return FALSE;
			if( !LogSetFileName(filename) )
				return FALSE;
			if( !LogSetLevel(level) )
				return FALSE;
			if( !LogSetConsoleOn(consoleOn) )
				return FALSE;
			if( !LogSetLogOn(logOn) )
				return FALSE;

	return TRUE;
}

int LogTruncate (char*filename)
{
			FILE *logfp;

			logfp = fopen (filename, "w");
			if (!logfp) {
				return FALSE;
			}
			fclose (logfp);
			return TRUE;
}

int LogSetLevel (int level)
{
			iLogLevel = level;
			return TRUE;
}

int LogSetConsoleOn (int consoleOn)
{
			iToConsoleLog = consoleOn;
			return TRUE;
}

int LogSetLogOn (int logOn)
{
			iToLog = logOn;
			return TRUE;
}

int LogSetFileName (const char *logFileName)
{
			if (logFileName) {
				strcpy (strLogFileName, logFileName);
				return TRUE;
			}
			return FALSE;
}


int LogSetModName (const char* modName)
{
			if (modName) {
				strcpy (strModName, modName);
				return TRUE;
			}
			return FALSE;
}



int LogAppend (int iErrorLevel,const char * fmtLogMsg, ... )
{
			va_list args;
			char *fmt;
			int iMessageNum;

			int level;

		    char errorCode[8],errorMessage1[64]="",errorMessage2[256]="";
			char strLevel[128]="";

			int logfd;
			time_t curtime;
			char buf[256]="";
			char buf3[256]="";
			char buf4[256]="";/* logfilename格式: modelName.yyyymmdd*/
			char buf5[4096]="";


			if (iErrorLevel < iLogLevel)
				return FALSE;


			#ifdef RW_MULTI_THREAD
				pthread_mutex_lock(&g_logMutex);
			#endif


			time (&curtime);
			strftime (buf3, 50, "%y%m%d", localtime (&curtime));
			strcpy(buf4, strLogFileName);
			strcat(buf4, ".");
			strcat(buf4, buf3);

			strftime (buf, 50, "%Y-%m-%d %H:%M:%S || ", localtime (&curtime));

			if (iToLog) {
					logfd = open (buf4,O_RDWR|O_CREAT|O_APPEND,0666);

					if ( logfd < 3 )
					{
						perror(buf4);
						#ifdef RW_MULTI_THREAD
									pthread_mutex_unlock(&g_logMutex);
						#endif
						return FALSE;
					}
			}
			va_start (args, fmtLogMsg);

			sprintf(strLevel, "<%s> || %s || %d || ", strModName,strLogLevel,getpid());
			if (iToLog)
			{
					write (logfd,strLevel, strlen(strLevel));
					write (logfd,buf, strlen(buf));
			}

			vsprintf(buf5,fmtLogMsg,args);
			if (iToLog)
			{
				if (strlen(buf5) > 0 )
				{
		        		write(logfd,buf5,strlen(buf5));
				 } else {
		        		write(logfd,fmtLogMsg,strlen(fmtLogMsg));
				 }

			}
			#ifdef RW_MULTI_THREAD
				pthread_mutex_unlock(&g_logMutex);
			#endif


			if (iToConsoleLog) {
				fprintf (stdout, "%s", strLevel);
				fprintf (stdout, "%s", buf);
		    if (strlen(buf5) > 0 )
		    {
		            fprintf(stdout,"%s",buf5);
		    } else {
		            fprintf(stdout,"%s",fmtLogMsg);
		    }

				fflush (stdout);
			}

			va_end (args);
			if (iToLog)
				close (logfd);
			return TRUE;
}






