/* 
 * File:   Mutex.h
 * Author: oscar
 *
 * Created on September 18, 2015, 2:23 PM
 */

#ifndef MUTEX_H
#define	MUTEX_H

#include "TCB_list.h"
struct my_mutex
{
	TCB_list* lockThreads;
	int idMutex;
        int isBlock;
};

typedef struct my_mutex myMutex;

myMutex* create();
void initMutex();

#endif	/* MUTEX_H */
