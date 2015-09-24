/* 
 * File:   RoundRobin.h
 * Author: oscar
 *
 * Created on September 10, 2015, 10:25 AM
 */

#ifndef ROUNDROBIN_H
#define	ROUNDROBIN_H

#define NO_ERROR 0
#define ERROR -1

#define MAX_THREADS 129 // 128 threads aparte del main

#include "MyPthread.h"
#include "TCB.h"
#include "TCBQueue.h"
#include "Dispatcher.h"
#include "Timer.h"
#include <time.h>

void initRoundRobin();
void scheduler();
int crear(ucontext_t* newcontext);
int ready(TCB* thread);
int despacharSiguienteHilo();


TCB* getRunningContext();

int	Block(TCB* thread, TCB* waited_for);
void	Unblock(TCB* thread, TCB* waited_for);
void	Unblock_waiting_for_me(TCB* thread);
void	Kill(TCB* thread);
TCB*	Find_TCB(int tid);
int	No_threads_beside_main();
int wakeupThreads();
int wait(TCB* thread, double waitTime);

TCB* currentThread;
TCB_list* all_threads; // Contiene todos los hilos que no han finalizado
TCB_list* block_threads; // Contiene todos los hilos que esten bloqueados
TCB_list* wait_threads; // Contiene todos los hilos que esten bloqueados
TCB_queue *TCBReadyQueue; // Contiene todos los hilos en estado ready
// Contador para el siguiente thread id con el cual se creara el siguiente hilo
int next_threadID; 
// Cuenta cuantos hilos existen en un determinado tiempo
int threadCounter; 

#endif	/* ROUNDROBIN_H */

