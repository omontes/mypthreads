#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "MyPthread.h"

void *proc1(void *x) {

    int n1 = *((int *) x);
    while (n1 > 0) {
        if(n1==15){
            printf("Yield de T1\n");
            sleep(2);
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
            sleep(2);
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

    int t1= my_thread_create(proc1, 1, &proc1Limit);
    int t2= my_thread_create(proc2, 1, &proc2Limit);
    uthread_join(t1);
    uthread_join(t2);
    if(Is_main()==1){
        printf("Soy el hilo main\n");
    }
    printf("Main termino\n");

    return (EXIT_SUCCESS);
}


