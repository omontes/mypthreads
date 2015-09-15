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

void *hiloFinalizacion(void *x);
int my_thread_create(void *(*function)(void *), int argc, void *arg);
void crearContextoFinalizacion();
void my_thread_init();
void my_thread_yield();
void yieldTread();
int Is_main();


#endif	/* THREAD_H */
