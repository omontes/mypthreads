#include "RoundRobin.h"
#include <signal.h>
TCB* currentThread;
TCB_list* all_threads; // Contiene todos los hilos que no han finalizado
TCB_list* block_threads; // Contiene todos los hilos que esten bloqueados
TCB_queue *TCBReadyQueue; // Contiene todos los hilos en estado ready
// Contador para el siguiente thread id con el cual se creara el siguiente hilo
int next_threadID; 
// Cuenta cuantos hilos existen en un determinado tiempo
int threadCounter; 
/*
 * Inicializa el calendarizador de tipo round robin
 */
void initRoundRobin() {
    struct sigaction activador;
    activador.sa_handler = scheduler;
    setupTimer(activador);
    next_threadID = 0;
    threadCounter = 0;
    //Crear la cola de los hilos en estado ready
    TCBReadyQueue = TCB_queue_create();
    // Crear la lista de todos los hilos que no han finalizado
    all_threads = TCB_list_create();
    block_threads = TCB_list_create();

    ucontext_t current;
    currentThread = TCB_create(0, &current, READY);
}
/*
 * EL calendarizador con RoundRobin
 */
void scheduler() {

    int gotContext = 0;
    TCB* runningThread = getRunningContext();
    Save(runningThread);
    if (!gotContext) {
        gotContext = 1;
        lockSignals();
        if (TCBReadyQueue->size != 0) {
            TCB* nextThread = DequeueTCB(TCBReadyQueue);
            ready(currentThread);
            currentThread = nextThread;
            currentThread->state = RUNNING;
            unlockSignals();
            dispatch(nextThread);
            
        }
        else{
            wakeupThreads();
            dispatch(runningThread);
        }
    }
}
/*
 * Crear un nuevo contexto de tipo round robin
 */
int crear(ucontext_t* newContext) {

   if (threadCounter + 1 > MAX_THREADS) // Maximum number of threads reached. We don't create the thread.
    {
        return ERROR;
    }

    TCB* thread = TCB_create(threadCounter, newContext, READY);
    if (thread == NULL) {
        return ERROR;
    }

    next_threadID++;
    threadCounter++;

    int result = TCB_list_add(all_threads, thread);

    if (result == ERROR) {
        return ERROR;
    }

    
    /*Lo agrega en la cola con estado Ready*/
    thread->detached = 0;
    int rdy =ready(thread);
    /*
     * Si el tamano de la cola Tread Control Block es uno, entonces inicializa
     * el round robin
     */
    if (TCBReadyQueue->size == 1) {
        startTimer();
    }
    
    return rdy;
   
}
/*
 * Agrega a la cola el thread y lo pone en estado Ready, devuelde el estado 
 * si fue exitoso el procedimeinto.
 */
int ready(TCB* thread) {
    lockSignals();
    int could_enqueue = EnqueueTCB(TCBReadyQueue, thread);
    unlockSignals();
    if (could_enqueue == ERROR) {
        return ERROR;
    } else {
        
        thread->state = READY;
        return thread->thread_id;
    }
    
}
/*
 * Manda a ejecuccion el TCB que este en la cola y lo pone en ejecuccion
 */
int despacharSiguienteHilo() {
    
    /*Primero lo saca de la cola*/
    lockSignals();
    TCB* thread = DequeueTCB(TCBReadyQueue);
    unlockSignals();
    /*Valida si la cola esta vacia, es decir no hay ningun otro hilo, solo el 
     main*/
    
        
    int empty = TCB_queue_is_empty(TCBReadyQueue);
    
    if ((empty == 1) & (TCB_list_is_empty(block_threads) == 1)) {
        /*if (TCB_list_is_empty(block_threads) == 1) {
            pauseTimer();
        }*/
        //printf("entro\n");
        pauseTimer();
        currentThread = thread;
        currentThread->state = RUNNING;
        
        /*int wake = 0;
        wake = wakeupThreads();
        if (wake == 1) {
            printf("Inicio otra vez  el tiempo\n");
            startTimer();
        }*/
        dispatch(thread);
        //return NO_ERROR; // Ready queue emptied. All threads are now finished.
    }
    else{
        /*Pone al hilo en estado de ejecuccion*/
        currentThread = thread;
        currentThread->state = RUNNING;
        int wake = 0;
        wake = wakeupThreads();
        dispatch(thread);
        return ERROR; // If execution reached this point, an error ocurred
    }
   
}

/*
 * Obtiene el hilo que se esta ejecutando en ese momento
 */
TCB* getRunningContext() {
    return currentThread;
}

int Block(TCB* thread, TCB* waited_for)
{
	return TCB_block(thread, waited_for);
}

void Unblock(TCB* thread, TCB* waited_for)
{
	TCB_unblock(thread, waited_for);

	ready(thread);
}
/*
 * Esta funcion permite desbloquear el hilo que estaba esperando que terminara
 * el procedimiento que hacia este hilo
 */
void Unblock_waiting_for_me(TCB* thread)
{
	TCB_list_node* pointer = (thread->waiting_for_me)->front;

	while(pointer != NULL)
	{
		Unblock(pointer->data, thread);

		pointer = pointer->next;
	}
}

void Kill(TCB* thread)
{
        lockSignals();
	Unblock_waiting_for_me(thread);

	TCB_list_remove(all_threads, thread); // Removes thread from list of current threads

	threadCounter--;
	free(thread->waiting_for_me); // Frees list of threads blocked by the thread that exited
	free(thread); // Frees pointer to thread that exited
        unlockSignals();
}
/*
 * Encuentra el hilo en la lista de all_threads
 */
TCB* Find_TCB(int tid)
{
	return TCB_list_get(all_threads, tid);
}

int No_threads_beside_main()
{
	return threadCounter == 1;
}

int wait(TCB* thread, double waitTime) {
    lockSignals();
    int result = TCB_list_add(block_threads, thread);
    unlockSignals();
    if (result == ERROR) {
        return ERROR;
    } else {
        thread->waitTime = waitTime;
        thread->startTime = clock();
        thread->state = BLOCKED;
        return thread->thread_id;
    }
    
}
int wakeupThreads(){
    if(block_threads->front == NULL){
        return 0;
    }
    lockSignals();
    TCB* thread =block_threads->front->data;
    unlockSignals();
    if (thread->state == BLOCKED) {
        clock_t end;
        double total;
        end = clock();
        total = end - thread->startTime / (double) 1000;
        if (total > thread->waitTime) {
            printf("Despierta\n");
            TCB_list_remove(block_threads,thread);
            ready(thread);
            return 1;
        }
    }
    
    
}


