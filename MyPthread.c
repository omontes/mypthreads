#include "MyPthread.h"

ucontext_t* contextoTerminal;
ucontext_t* contextoDummy;
int main_tid; // thread id del hilo principal
int dummy_tid; //idle thread 

/*
 * Inicializa el roundRobin y guarda el contexto principal
 */
void my_thread_init() {
    int gotcontext = 0;
    ucontext_t* main_context = (ucontext_t*)malloc(sizeof(ucontext_t));
    crearContextoFinalizacion();
    initRoundRobin(); // Inicializa el round robin
    getcontext(main_context);
    if (!gotcontext) {
        gotcontext = 1;
        main_tid = crear(main_context); // Creates main thread
        crearContextoDummy();
        despacharSiguienteHilo();


    }

}
/*
 *Esta funcion crea el contexto del nuevo hilo y le asigna el contexto de fina-
 * lizacion para cuando el hilo termine, que ejecute ese contexto al finalizar.
 */
int my_thread_create(void *(*function)(void *), int argc, void *arg) {
    ucontext_t* nuevoHilo = make_context(function, arg, contextoTerminal);
    return crear(nuevoHilo);
}

void crearContextoDummy(){
    contextoDummy = make_context(dummyFunction, 0, 0);
    dummy_tid = crear(contextoDummy); // Creates dummy thread
    despacharSiguienteHilo();
}
void *dummyFunction(void *x){
    while(1);
}
/*
 * Crear el contexto que todos los hilos llaman al finalizar su funcion
 */
void crearContextoFinalizacion() {
    contextoTerminal = make_context(hiloFinalizacion, 0, 0);
}
/*
 * La funcion del contexto de finalizacion
 */
void *hiloFinalizacion(void *x) {
    TCB* thread = getRunningContext();
    Kill(thread);
    despacharSiguienteHilo();

}
/*
 * Implementa la funcion yield al cambiar de contexto de ejecuccion
 */
void my_thread_yield() {

    int gotYield = 0;
    /*Guarda el contexto del hilo que se esta ejecutando*/
    Save(getRunningContext());

    if (!gotYield) {
        gotYield = 1;
        /*Realiza el cambio de contexto por otro hilo de la cola de los listos*/
        yieldTread();
    } else {
        return;
    }

}
/*
 * Realiza el cambio de contexto y ejecuta el siguiente hilo 
 */
void yieldTread() {
    ready(getRunningContext());
    despacharSiguienteHilo();
}
/*
 * Realiza un join del hilo con el que el hilo  que llama al join debe esperar
 */
int my_thread_join(int waited_thread_tid)
{
        //El hilo que estaba corriendo y que llamo al join
	TCB* this_thread = getRunningContext();
        //El hilo que tiene que ejecutarse sin problemas y que no se bloquea
	TCB* waited_thread = Find_TCB(waited_thread_tid);

	if(waited_thread == NULL) 
	{
		return ERROR;
	}
	
	Block(this_thread, waited_thread); // Blocks this thread's TCB

	Save(this_thread); // Saves 'here' as current thread context.

	if(TCB_is_blocked(this_thread)) // Stop thread only if thread is blocked.
	{
                //printf("antes de main termino\n");
		return despacharSiguienteHilo();
	}
	else // If thread isn't blocked, we're returning to this point via context switching: we don't stop the thread, just return.
	{
                printf("ya el thread no esta bloqueado\n");
		return NO_ERROR;
	}
}

void my_thread_wait(double segundos){
    int gotContext = 0;
    TCB* wait_thread = getRunningContext();
    Save(wait_thread);
    if (gotContext == 0) {
        gotContext = 1;
        wait(wait_thread, segundos);
        despacharSiguienteHilo();
    }
    else{
        return;
    }
    
    
} 
int Is_main()
{
	TCB* current_thread = getRunningContext();
	return current_thread->thread_id == main_tid;
}
