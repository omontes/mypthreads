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

	int contador_sockets;
	for(contador_sockets = 0; contador_sockets < 2;contador_sockets++){
		 if(contador_sockets == 0)
		 	socket_monitor_1 = listener((void*)&sock);
		 else
		 	socket_monitor_2 = listener((void*)&sock);
	}


	pthread_t monitor_1;
	pthread_t monitor_2;
	if ( pthread_create(&monitor_1, NULL, accept_client, (void*)&socket_monitor_1) < 0 ){
			perror("Thread problem\n");
			return 1;
		}
	if ( pthread_create(&monitor_2, NULL, accept_client, (void*)&socket_monitor_2) < 0 ){
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
	endwin();

	endwin();
	exit(0);
}
