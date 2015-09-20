#include "tserver.h"
int main(int argc, char*argv[]){
	//signal(SIGPIPE,SIG_IGN);

	int ch;
	show_ncurs();
	int sock=open_socket();
	if(sock==-1){
		printf("error occured\n");
		return -1;
	}
        /*Inicializa los sockets de los monitores 1 y 2*/
	int contador_sockets;
	for(contador_sockets = 0; contador_sockets < 1;contador_sockets++){
		 if(contador_sockets == 0){
                        printw("creo monitor 1\n");
                        refresh();
                        socket_monitor_1 = listener((void*)&sock);}
		 else
		 	socket_monitor_2 = listener((void*)&sock);
	}
        printw("ya cree todos los sockets\n");
        refresh();

        /*Crea las figuras del archivo de configuracion*/
	pthread_t hilofigura1;
	pFigura* fig1 = figura_create(1, 0, 0, 0, 1, 2, 1,2000000,10,1,1,1,50,5);
	if ( pthread_create(&hilofigura1, NULL, pintame, (void*)fig1) < 0 ){
			perror("Thread problem\n");
			return 1;
		}
        pthread_t hilofigura2;
        pFigura* fig2 = figura_create(2, 0, 5, 0, 3, 4, 1,2000000,10,1,1,1,50,10);
	if ( pthread_create(&hilofigura2, NULL, pintame, (void*)fig2) < 0 ){
			perror("Thread problem\n");
			return 1;
		}
    

    //Exit
	while(1){
		ch = getch();
		if(ch=='q'){
                        
			break;
		}
	
	}
        close(socket_monitor_1);
	endwin();

	endwin();
	exit(0);
}
