#include "Dispatcher.h"
/*
 * Pone en la ejecuccion el thread. Agrega todos sus registros al procesador
 */
void dispatch(TCB* thread) {
    setcontext(thread->context);
}
/*
 * Guarda el contexto de un hilo y almacena su estado de ejecuccion
 */
int Save(TCB* thread) {
    int success = getcontext(thread->context);
    return success;
}
