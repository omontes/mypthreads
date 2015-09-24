#include "Timer.h"
#include <stdio.h>
#include "stdlib.h"
/*
 * Bloquea todas la senales del sistema
 */
void lockSignals() {
    sigemptyset(&t1);
    sigaddset(&t1, SIGPROF); 
    sigprocmask(SIG_BLOCK, &t1, &t2); 
}
/*
 * Desbloquea todas la senales del sistema
 */
void unlockSignals() {
    sigprocmask(SIG_SETMASK, &t2, NULL);
}
/*
 * Configura el timer con la funcion de activacion en el struct act, donde en 
 * el round robin es la funcion schedule
 */
void setupTimer(struct sigaction act){
    struct sigaction oact;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;

    sigaction(SIGPROF, &act, &oact);

    it.it_interval.tv_sec = 0;
    it.it_interval.tv_usec = INTERVAL;
    it.it_value.tv_sec = 0;
    it.it_value.tv_usec = START;
}
/*
 * Inicia el timer
 */
void startTimer(){
    setitimer(ITIMER_PROF, &it, NULL); 
}
/*
 * Pausa el timer
 */
void pauseTimer() {
    struct itimerval zero_timer = {0};
    setitimer(ITIMER_PROF, &zero_timer, &it);
}