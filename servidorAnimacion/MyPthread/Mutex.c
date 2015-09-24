#include "Mutex.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*
 * Esta funcion inicializa un mutex
 */
myMutex* create(){
    myMutex* new_mutex = (myMutex*)malloc(sizeof(myMutex));
    if(new_mutex == NULL)
	{
		return NULL;
	}
	else
	{
		new_mutex->idMutex = 0;
		new_mutex->lockThreads = TCB_list_create();
                new_mutex->isBlock = 0;

		return new_mutex;
	}
}