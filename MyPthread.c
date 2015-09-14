#include "MyPthread.h"

ucontext_t* contextoTerminal;

void my_thread_init() {

    crearContextoFinalizacion();
    initRoundRobin(); // Inicializa el round robin

}
/*
 *Esta funcion crea el contexto del nuevo hilo y le asigna el contexto de fina-
 * lizacion para cuando el hilo termine, que ejecute ese contexto al finalizar.
 */
void my_thread_create(void *(*function)(void *), int argc, void *arg) {
    ucontext_t* nuevoHilo = make_context(function, arg, contextoTerminal);
    crear(nuevoHilo);
}
/*
 * Crear el contexto que todos los hilos llaman al finalizar su funcion
 */
void crearContextoFinalizacion() {
    contextoTerminal = make_context(contextoFinalizacion, 0, 0);
}
/*
 * La funcion del contexto de finalizacion
 */
void *contextoFinalizacion(void *x) {

    // TCB* thread = Running();
    //kill que hace free()

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




