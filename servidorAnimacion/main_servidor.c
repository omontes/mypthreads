#include "tserver.h"
#include "MyPthread/MyPthread.h"
#include "MyPthread/MyMutex.h"
#include "MyPthread/TCB.h"
myMutex* mt;
void sig_int(int signo)
{       
        close(socket_monitor_1);
        close(socket_monitor_2);
	printf("Exit\n");
	exit(0);
}
int main(int argc, char*argv[]){
	
        //init socket ***
    
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
	for(contador_sockets = 0; contador_sockets < 2;contador_sockets++){
		 if(contador_sockets == 0){          
                        socket_monitor_1 = listener((void*)&sock);
                        printf("creo monitor 1\n");}
		 else   {
		 	socket_monitor_2 = listener((void*)&sock);
                        printf("creo monitor 2\n");
                 }
	}
        printf("ya cree todos los sockets\n");
        
        my_thread_init();
        my_mutex_init();
        mt = my_mutex_create();
              
        //init lista
        initLista();

      
	pFigura* fig1 = figura_create(1, 0, 0, 0, 1, 2, 1,300,1,0,1,1,40,0,25000,asignarMonitor(0),0);
        pFigura* fig2 = figura_create(2, 40, 0, 0, 5, 6, 1,200,1,0,-1,1,0,0,45000,asignarMonitor(40),0);
        pFigura* fig3 = figura_create(3, 0, 8, 0, 3, 4, 1,500,1,0,1,1,80,8,40000,asignarMonitor(0),5000);
        pFigura* fig4 = figura_create(4, 120, 8, 0, 6, 7, 1,700,1,0,-1,1,0,8,60000,asignarMonitor(120),2000);
        agregarFiguraLista(fig1);
        agregarFiguraLista(fig2);
        agregarFiguraLista(fig3);
        agregarFiguraLista(fig4);
        
        int t1 =my_thread_create(pintame, 1, (void*)fig1,1,0);
        int t2 = my_thread_create(pintame, 1, (void*)fig2,1,0);
        int t3 = my_thread_create(pintame, 1, (void*)fig3,1,0);
        int t4 = my_thread_create(pintame, 1, (void*)fig4,1,0);
        
  
    	while(1);
        //my_thread_join(t3);
       
       
		
	//close(socket_monitor_1);
        //close(socket_monitor_2);
	printf("Exit\n");
	exit(0);
}


