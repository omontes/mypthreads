#include "MyMutex.h"
int mutexCounter;
/*
 * Esta funcion crea un mutex 
 */

void my_mutex_init() {
    mutexCounter = 0;
    
}

myMutex* my_mutex_create(){
       myMutex* newMutex = create();
       mutexCounter++;
       return newMutex;
}


