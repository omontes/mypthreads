#include <stdio.h>
#include <stdlib.h>
#include "tclient.h"
int main(int argc, char*argv[]){
    
      
	
	char buf[1023];
        //mostrar pantalla
	show_ncurs();
               
        //Coneccion con el servidor
	struct sockaddr_in saddr;
	saddr.sin_family=AF_INET;
	saddr.sin_port=htons(1021);
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
        initLista();
        while(1){
            
                //recibir datos del server
		num=recv(sock,buf,1023,0);                         
                
                
		buf[num]='\0';
		if(num==0){
			break;
		}
                //convertir dato de server a struct
                pFigura* fig = (pFigura*)malloc(sizeof(pFigura));
		unser(fig,buf);
               
                //mvwprintw(status_w,3,2,"yinit%d\n",fig->y_init);
                //wrefresh(status_w);
                
                //limpiar ventana
		wclear(field_w);
                
                
		if(verificarEnableFigura(fig)==1){
                    procesarFiguraEntrante(fig);
                }
                else{
                    eliminarFiguraEntrante(fig);
                }
                 
                pintarFigurasMonitor(field_w);
                wrefresh(field_w);


		buf[0]='\0';
	}
	close(sock);
	endwin();
	return 0;
}
