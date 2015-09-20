#include <stdio.h>
#include <stdlib.h>
#include "tclient.h"
int main(int argc, char*argv[]){
	
	char msg[1023];
	char buf[1023];
	show_ncurs();
	struct sockaddr_in saddr;
	saddr.sin_family=AF_INET;
	saddr.sin_port=htons(124);
	saddr.sin_addr.s_addr=inet_addr("127.0.0.1");
	int sock;
	if((sock=socket(PF_INET,SOCK_STREAM,0))==-1){
		mvwprintw(status_w,2,2,"Something wrong with socket!\n",status_w);
		wrefresh(status_w);
		endwin();
		return 1;
	}


	int c=sizeof(saddr);
	int status = connect(sock,(struct sockaddr*)&saddr,(socklen_t)c);
	if(status<0){mvwprintw(status_w,2,2,"Connection error.\n",status_w);wrefresh(status_w);endwin();exit(1);}
	mvwprintw(status_w,2,2,"Connection established.\n");
	wrefresh(status_w);

	int num;
	while(1){

		num=recv(sock,buf,1023,0);
		buf[num]='\0';
		if(num==0){
			break;
		}

                pFigura* new_figure = (pFigura*)malloc(sizeof(pFigura));

		unser(new_figure,buf);
		
		wclear(field_w);

		printFigure1(field_w,new_figure->x_init,new_figure->y_init,new_figure->rotation,new_figure->colorIn,new_figure->colorOut);
		wrefresh(field_w);


		buf[0]='\0';

		
	}
	close(sock);
	endwin();
	return 0;
}
