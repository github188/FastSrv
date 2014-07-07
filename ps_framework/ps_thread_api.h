#ifndef __PS_THREAD_API_H__
#define __PS_THREAD_API_H__

/* c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
/* linux */
#include <stdint.h>
#include <errno.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/types.h>
/* thread pool */
#include <pthread.h>
#include <list>

int thread_pool_init();
void thread_pool_destroy();
int thread_pool_add(unsigned int size,void*(*event)(void*));
void task_destroy();
int task_init();
void task_destroy();
int task_push(void* task);
int task_pop(void** task);

// __PS_THREAD_API_H__
#endif
