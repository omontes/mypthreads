#include "RoundRobin.h"
#include <signal.h>

/*
 * Inicializa el calendarizador de tipo round robin
 */
void initRoundRobin() {
    struct sigaction activador;
    activador.sa_handler = scheduler;
    setupTimer(activador);
    next_threadID = 0;
    threadCounter = 0;
    flag = 0;
    //Crear la cola de los hilos en estado ready
    TCBReadyQueue = TCB_queue_create();
    // Crear la lista de todos los hilos que no han finalizado
    all_threads = TCB_list_create();
    block_threads = TCB_list_create();
    wait_threads = TCB_list_create();
    sorted_threads = TCB_list_create();

    ucontext_t current;
    currentThread = TCB_create(0, &current, READY,1,0);
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
        if (TCBReadyQueue->size != 0 | sorted_threads->size!=0) {
            TCB* nextThread;
            if (flag == 0) {//TENER CUIDADO CON QUE TCBReadyQueue este vacia
                //printf("lo ultimo que veo\n");
                if (TCBReadyQueue->size == 0) {
                    //TCB* nextThread2 = obtenerMaximoTiquetes();
                    //printf("nextThread: %d\n", nextThread2->thread_id);
                    nextThread = obtenerMaximoTiquetes();
                    TCB_list_remove(sorted_threads, nextThread);
                    flag = 1;
                } else {
                    nextThread = DequeueTCB(TCBReadyQueue);
                    flag = 1;
                }
            } else if(flag==1) {
                if (sorted_threads->size == 0) {
                    nextThread = DequeueTCB(TCBReadyQueue);
                    flag=0;
                    

                } else if(sorted_threads->size > 0) {
                    /*TCB* nextThread2 = obtenerMaximoTiquetes();
                    printf("nextThread: %d\n", nextThread2->thread_id);*/
                    nextThread = obtenerMaximoTiquetes();
                    TCB_list_remove(sorted_threads, nextThread);
                    flag=0;
                    
                }
                

            }
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
int crear(ucontext_t* newContext, int tipo, int tiquetes) {

   if (threadCounter + 1 > MAX_THREADS) 
    {
        return ERROR;
    }

    TCB* thread = TCB_create(threadCounter, newContext, READY, tipo, tiquetes);
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
    thread->waitTime = 0;
    thread->startTime = 0;
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
TCB* obtenerMaximoTiquetes(){
    if(sorted_threads->size == 1){
        return sorted_threads->front->data;
    }
    TCB_list_node* pointer = sorted_threads->front;
    int totalTiquetes = 0;
    /*Suma el total de tiquetes*/
    while(pointer != NULL)
    {
        TCB* thread =pointer->data;
        totalTiquetes+=thread->tiquetes;
        
        pointer = pointer->next;
    }
    int maximoTiquetes=rand()%totalTiquetes;
    printf("total tiquets: %d\n",totalTiquetes);
    printf("cantidad hilos: %d\n",sorted_threads->size);
    printf("random tiquets: %d\n",maximoTiquetes);
    /*Vuelve a recorrer la lista para elegir el ganador*/
    pointer = sorted_threads->front;
    TCB* thread = (TCB*) malloc(sizeof (TCB));
    int tiquetesAcumulados=0;
    while(pointer != NULL)
    {
        TCB* thread =pointer->data;
        printf("id candidato: %d\n",thread->thread_id);
        
        if(maximoTiquetes <= (thread->tiquetes + tiquetesAcumulados))
            return thread;
        tiquetesAcumulados = thread->tiquetes;
        pointer = pointer->next;
        
    }
    printf("llegue aqui\n");
    return thread;
    
}
/*
 * Agrega a la cola el thread y lo pone en estado Ready, devuelde el estado 
 * si fue exitoso el procedimeinto.
 */
int ready(TCB* thread) {
    lockSignals();
    int could_enqueue = 0;
    if (thread->tipo == 1) {
         could_enqueue = EnqueueTCB(TCBReadyQueue, thread);
    }
    else if (thread->tipo == 2){
        could_enqueue = TCB_list_add(sorted_threads, thread);
        
    }
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
    TCB* thread;
    if (flag == 0) {
        lockSignals();
        thread = DequeueTCB(TCBReadyQueue);
        flag = 1;
        unlockSignals();
    } else if (flag == 1) {
        if (sorted_threads->size == 0) {
            lockSignals();
            thread = DequeueTCB(TCBReadyQueue);
            flag = 0;
            unlockSignals();


        } else if(sorted_threads->size > 0) {
            lockSignals();
            thread = sorted_threads->front->data;
            TCB_list_remove(sorted_threads, thread);
            flag = 0;
            unlockSignals();
        }



    }
    
    /*Valida si la cola esta vacia, es decir no hay ningun otro hilo, solo el 
     main*/
    currentThread = thread;
    currentThread->state = RUNNING;
    int wake = 0;
    wake = wakeupThreads();
    dispatch(thread);
    return ERROR;
    
   
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
    int result = TCB_list_add(wait_threads, thread);
    unlockSignals();
    if (result == ERROR) {
        return ERROR;
    } else {
        clock_t start = clock();
        thread->waitTime = waitTime;
        thread->startTime = start;
        thread->state = BLOCKED;
        return thread->thread_id;
    }
    
}
int wakeupThreads(){
    
    if(wait_threads->front == NULL){
        return 0;
    }
    lockSignals();
    TCB* thread =wait_threads->front->data;
    unlockSignals();
    if (thread->state == BLOCKED) {
        clock_t end;
        double total;
        end = clock();
        total = (end - thread->startTime) / (double) 1000;
        if (total > thread->waitTime) {
            TCB_list_remove(wait_threads,thread);
            ready(thread);
            return 1;
        }
    }
    
    
}


