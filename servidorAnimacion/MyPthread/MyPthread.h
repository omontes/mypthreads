/* 
 * File:   MyPthread.h
 * Author: oscar
 *
 * Created on September 10, 2015, 9:25 AM
 */
#ifndef THREAD_H
#define	THREAD_H

#include "ucontext.h"
#include <stdio.h>
#include "stdlib.h"
#include "ContextManage.h"
#include "RoundRobin.h"
#include "Dispatcher.h"
#include "Mutex.h"
void my_thread_end();
int my_thread_create(void *(*function)(void *), int argc, void *arg, int tipo, int tiquetes);
void crearContextoFinalizacion();
void my_thread_init();
void my_thread_yield();
void yieldTread();
int Is_main();
void my_thread_wait(double segundos);
void crearContextoDummy();
void *dummyFunction(void *x);
void my_thread_detach(int thread_id);
void my_mutex_block(myMutex* mt);


#endif	/* THREAD_H */

