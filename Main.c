#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "MyPthread.h"
#include "MyMutex.h"
#include "TCB.h"
int share;
myMutex* mt;
void *proc1(void *x) {

    int n2 = *((int *) x);
    while (n2 > 0) {
        if(n2==5){
            printf("N2:%d\n", n2);
            /*my_thread_wait(2000000);
            printf("Finalizo T1 por end\n");
            my_thread_end();*/
            //printf("Yield de T1\n");
            my_thread_wait(5000);
            //my_thread_yield();
        }
        printf("N2:%d\n", n2--);
    }
    printf("Finalizo hilo 2\n");
}

void *proc2(void *x) {

    int n3 = *((int *) x);
    while (n3 > 0) {
        /*if(n2==3){
            //printf("Yield de T2\n");
            //my_thread_yield();
        }*/
        printf("N3:%d\n", n3--);
    }
    printf("Finalizo hilo 3\n");
    my_thread_wait(2000);
    

}
void *shareProc(void *x) {
    my_mutex_block(mt);
    while (share > 0) {
        printf("N:%d con hilo%d\n",share,getRunningContext()->thread_id);
        share--;
        my_thread_wait(1000);//Espera un segundo
    }
    my_mutex_unblock(mt);
    share = 10;

}

int main(int argc, char** argv) {

    share = 10;

    int proc1Limit = 25;
    int proc2Limit = 5;

    my_thread_init();
    my_mutex_init();
    mt =my_mutex_create();
    
   
    /*int t1= my_thread_create(shareProc, 1, NULL, 1, 0);//id2
    int t2= my_thread_create(shareProc, 1, NULL, 2, 100);//id3
    int t3= my_thread_create(shareProc, 1, NULL, 1, 0);//id4*/
    
    int t1= my_thread_create(proc1, 1, &proc1Limit,1,0);//id2
    int t2= my_thread_create(proc2, 1, &proc2Limit,1,0);//id3
    
  
    //my_thread_detach(t1);
    //my_thread_detach(t2);
   
     my_thread_join(t1);
     my_thread_join(t2);
     //my_thread_join(t3);
   
    printf("Main termino\n");

    return (EXIT_SUCCESS);
}


