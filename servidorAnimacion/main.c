#include "tserver.h"

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
        

        /*Crea las figuras del archivo de configuracion*/
	pthread_t hilofigura1;
	pFigura* fig1 = figura_create(1, 0, 0, 0, 1, 2, 1,2000000,10,1,1,1,50,5);
	if ( pthread_create(&hilofigura1, NULL, pintame, (void*)fig1) < 0 ){
			perror("Thread problem\n");
			return 1;
		}
        pthread_t hilofigura2;
        pFigura* fig2 = figura_create(2, 0, 5, 0, 3, 4, 1,3000000,10,1,1,1,50,10);
	if ( pthread_create(&hilofigura2, NULL, pintame, (void*)fig2) < 0 ){
			perror("Thread problem\n");
			return 1;
		}
    

    	while(1);
		
	
	
        close(socket_monitor_1);

	exit(0);
}


