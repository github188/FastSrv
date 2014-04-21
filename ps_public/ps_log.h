#ifndef __PS_LOG_H__
#define __PS_LOG_H__

#define LOG_SCREEN(x) {			\
	printf(x);					\
	fflush(stdout);				\
}

#define LOG_TRACE(x,y,...) {					\
	printf(x);					\
	fflush(stdout);				\
}

// __PS_LOG_H__
#endif
