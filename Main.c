#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "MyPthread.h"
#include "MyMutex.h"
#include "TCB.h"

void *proc1(void *x) {

    int n1 = *((int *) x);
    while (n1 > 0) {
        if(n1==15){
            /*printf("N1:%d\n", n1);
            my_thread_wait(2000000);
            printf("Finalizo T1 por end\n");
            my_thread_end();*/
            printf("Yield de T1\n");
            my_thread_yield();
        }
        printf("N1:%d\n", n1--);
    }
    printf("Finalizo T1\n");
}

void *proc2(void *x) {

    int n2 = *((int *) x);
    while (n2 > 0) {
        if(n2==3){
            printf("Yield de T2\n");
            my_thread_yield();
        }
        printf("N2:%d\n", n2--);
    }
    printf("Finalizo T2\n");
    sleep(2);

}

int main(int argc, char** argv) {


    int proc1Limit = 25;
    int proc2Limit = 5;

    my_thread_init();
    my_mutex_init();
    myMutex* mt =my_mutex_create();
    //my_mutex_block(mt);
    printf("el mutex esta bloqueado: %d\n",mt->isBlock);
    //my_thread_wait(10000000);
    int t1= my_thread_create(proc1, 1, &proc1Limit);
    int t2= my_thread_create(proc2, 1, &proc2Limit);
    //my_thread_detach(t1);
    //my_thread_detach(t2);
    my_thread_join(t1);
    my_thread_join(t2);
    printf("Hi\n");
    my_thread_wait(5000000);
    printf("Main termino\n");

    return (EXIT_SUCCESS);
}


