#include "tserver.h"
#include "MyPthread/MyPthread.h"
#include "MyPthread/MyMutex.h"
#include "MyPthread/TCB.h"
myMutex* mt;
void sig_int(int signo)
{       
        close(socket_monitor_1);
	printf("Exit\n");
	exit(0);
}
int main(int argc, char*argv[]){
	
        struct sigaction sa;
        sa.sa_handler = &sig_int;
        // Block every signal during the handler
        sigfillset(&sa.sa_mask);
        if (sigaction(SIGINT, &sa, NULL) == -1) {
        printf("Error: cannot handle SIGINT"); 
        }

	int sock=open_socket();
	if(sock==-1){
		printf("error occured\n");
		return -1;
	}
        /*Inicializa los sockets de los monitores 1 y 2*/
	int contador_sockets;
	for(contador_sockets = 0; contador_sockets < 1;contador_sockets++){
		 if(contador_sockets == 0){
                        printf("creo monitor 1\n");
                        
                        socket_monitor_1 = listener((void*)&sock);}
		 else
		 	socket_monitor_2 = listener((void*)&sock);
	}
        printf("ya cree todos los sockets\n");
        
        my_thread_init();
        my_mutex_init();
        mt = my_mutex_create();

      
	pFigura* fig1 = figura_create(1, 0, 0, 0, 1, 2, 1,2000,10,1,1,1,50,5);
        int t1 =my_thread_create(pintame, 1, (void*)fig1);
        
        pFigura* fig2 = figura_create(2, 0, 5, 0, 3, 4, 1,3000,10,1,1,1,50,10);
	int t2 = my_thread_create(pintame, 1, (void*)fig2);
    

    	my_thread_join(t1);
        my_thread_join(t2);
		
	close(socket_monitor_1);
	printf("Exit\n");
	exit(0);
}


