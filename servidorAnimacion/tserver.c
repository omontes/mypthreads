#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <string.h>
#include <ncurses.h>
#include <pthread.h>
#include <signal.h>

#include <unistd.h>


#define DELAY 5000000

// gcc with -lpthread -lncurses

struct message {

	int length;
	char* msg;

	//Id
	int  id;
	

	//Position
	int x_init;
	int y_init;

	//Direction
	char direction; //'0' : +x , '1': -x, '2': +y, '3': -y

	//Degrees rotation figure
	int rotation;  //0,90,180,270


	//Color Figure
	int colorIn; 
	int colorOut;

};

struct message msg_net;

void show_ncurs();
int open_socket();
void* accept_client();
int listener(void*sock);


//socket

int socket_monitor_1;
int socket_monitor_2;


// Serialize
void ser(struct message*, char*);




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


int open_socket(){
	struct sockaddr_in saddr;
	saddr.sin_family=AF_INET;
	saddr.sin_port=htons(124);
	saddr.sin_addr.s_addr=INADDR_ANY;
	int s;
	if((s=socket(PF_INET,SOCK_STREAM,0))==-1){
		printw("Something wrong with socket!\n");
		refresh();
	}
	if(bind(s,(struct sockaddr*)&saddr,(socklen_t)(sizeof(saddr)))<0){
		printw("Bind error!\n");
		refresh();
		return -1;
	}
	printw("Server Started and is Listening...\n");
	refresh();
	if(listen(s,3)==-1){
		printw("Listen failed\n");
		refresh();
	}
	return s;
}




void *accept_client(void* ns){
	char msg[1023];
	char buf[1023];

	strcpy(msg,"hola mundo");
	int num,lol=1;
	int my_sock=*(int*)ns;
	int cont = 0;
	while(1){
		
		if(cont == 20)
			cont = 0;
		
		msg_net.x_init = cont;
		cont++;
		msg_net.y_init = 10;
		msg_net.msg=msg;
		msg_net.length=sizeof(char)*(strlen(msg)+1);

		printw("%d\n",msg_net.length);
		printw("%s\n",msg_net.msg);

		ser(&msg_net, buf);
		send(my_sock,buf,sizeof(buf),0);

		usleep(DELAY);
		refresh();
		buf[0]='\0';




	}
	close(my_sock);
}

void ser(struct message *m, char* buf){



	memcpy(buf, &m->length, sizeof(int));
	memcpy(buf+sizeof(int), m->msg, m->length);

	//Id
	memcpy(buf +2*sizeof(int), &m->x_init, sizeof(int));

	//Position
	memcpy(buf +3*sizeof(int), &m->x_init, sizeof(int));
	memcpy(buf +4*sizeof(int), &m->y_init, sizeof(int));
}





int listener(void*sock){
	struct sockaddr_in client;
	int m_sock=*(int*)sock;
	int new_sock;
	int c=sizeof(struct sockaddr_in);
		
	while ( new_sock = accept(m_sock,(struct sockaddr*)&client,(socklen_t*)&c) ){
		
		printw("Connection accepted.\n");
		refresh();
		break;
	}
	return new_sock;
}




//Terminal
void show_ncurs(){
int row,col;
	initscr();
	raw();
	keypad(stdscr, true);
	//noecho();
	
	getmaxyx(stdscr,row,col);

}
