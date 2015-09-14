#include "RoundRobin.h"
#include <signal.h>
TCB* currentThread;
TCB_list* all_threads; // Contiene todos los hilos que no han finalizado
TCB_queue *TCBReadyQueue; // Contiene todos los hilos en estado ready
// Contador para el siguiente thread id con el cual se creara el siguiente hilo
int next_threadID = 0; 
// Cuenta cuantos hilos existen en un determinado tiempo
int threadCounter = 0; 
/*
 * Inicializa el calendarizador de tipo round robin
 */
void initRoundRobin() {
    struct sigaction activador;
    activador.sa_handler = scheduler;
    setupTimer(activador);
    
    //Crear la cola de los hilos en estado ready
    TCBReadyQueue = TCB_queue_create();
    // Crear la lista de todos los hilos que no han finalizado
    all_threads = TCB_list_create();

    ucontext_t current;
    currentThread = TCB_create(0, &current, READY);
}
/*
 * EL calendarizador con RoundRobin
 */
void scheduler() {

    int gotContext = 0;
    Save(getRunningContext());

    if (!gotContext) {
        gotContext = 1;
        lockSignals();
        TCB* nextThread = DequeueTCB(TCBReadyQueue);
        ready(currentThread);
        currentThread = nextThread;
        currentThread->state = RUNNING;
        unlockSignals();
        dispatch(nextThread);
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
void despacharSiguienteHilo() {
    /*Primero lo saca de la cola*/
    lockSignals();
    TCB* thread = DequeueTCB(TCBReadyQueue);
    unlockSignals();
    /*Valida si la cola esta vacia, es decir no hay ningun otro hilo, solo el 
     main*/
    int empty = TCB_queue_is_empty(TCBReadyQueue);
    if (empty == 1) {
        pauseTimer();
    }
    /*Pone al hilo en estado de ejecuccion*/
    currentThread = thread;
    currentThread->state = RUNNING;
    /*Setea el contexto del hilo*/
    dispatch(thread);
}

/*
 * Obtiene el hilo que se esta ejecutando en ese momento
 */
TCB* getRunningContext() {
    return currentThread;
}

