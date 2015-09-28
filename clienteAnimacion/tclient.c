#include "tclient.h"
pFigura* unser(pFigura *figura, char* buf){

	

	//ID
	memcpy(&figura->id, buf, sizeof(int));

	//Position
	memcpy(&figura->x_init, buf +1*sizeof(int), sizeof(int));
	memcpy(&figura->y_init, buf +2*sizeof(int), sizeof(int));
        
        //Rotacion
	memcpy(&figura->rotation, buf +3*sizeof(int), sizeof(int));
	
        //Colores
	memcpy(&figura->colorIn, buf +4*sizeof(int), sizeof(int));
	memcpy(&figura->colorOut, buf +5*sizeof(int), sizeof(int));
        
        //Enable
        memcpy(&figura->enable, buf +6*sizeof(int), sizeof(int));
        
}

void initLista(){
    listaFigurasMonitor = list_create();
    
}

int verificarEnableFigura(pFigura* figura){
    if(figura->enable == 1){
        return 1;
    }
    else{
        return 0;
    }
}

void procesarFiguraEntrante(pFigura* figura){
    if(list_is_empty(listaFigurasMonitor)){
        list_add(listaFigurasMonitor, figura);
        
    } else {
        
        pFigura* fig = list_get(listaFigurasMonitor, figura->id);
        if (fig == NULL) {
            list_add(listaFigurasMonitor, figura);
            
        }
        else{
            fig->x_init = figura->x_init;
            fig->y_init = figura->y_init;
            fig->rotation = figura->rotation;
            
        }
    }
}


void pintarFigurasMonitor(WINDOW* win){
    pNodo* pointer = listaFigurasMonitor->front;

    while(pointer != NULL)
    {
       
        pFigura* fig =pointer->data;
        printFigure1(win,fig->y_init,fig->x_init,fig->rotation,fig->colorIn,fig->colorOut);
        
        pointer = pointer->next;
    }

    
};


void eliminarFiguraEntrante(pFigura* figura){
    list_remove(listaFigurasMonitor,figura);
}


//Terminal

void draw_borders(WINDOW *screen) {
      int x, y, i;
      getmaxyx(screen, y, x);
      // 4 corners
      mvwprintw(screen, 0, 0, "+");
      mvwprintw(screen, y - 1, 0, "+");
      mvwprintw(screen, 0, x - 1, "+");
      mvwprintw(screen, y - 1, x - 1, "+");
     

      // top and bottom
      for (i = 1; i < (x - 1); i++) {
        mvwprintw(screen, 0, i, "-");
        mvwprintw(screen, y - 1, i, "-");
      }
    }

void show_ncurs(){
	int row,col;
	int status_size = 5;
	
	initscr();
	start_color();

	 //colors
 	init_pair(1,COLOR_BLACK,COLOR_RED);
 	init_pair(2,COLOR_BLACK,COLOR_GREEN);
 	init_pair(3,COLOR_BLACK,COLOR_BLUE);
	init_pair(4,COLOR_BLACK,COLOR_YELLOW);
	init_pair(5,COLOR_BLACK,COLOR_MAGENTA);
	init_pair(6,COLOR_BLACK,COLOR_CYAN);
	init_pair(7,COLOR_BLACK,COLOR_WHITE);


	noecho();
	curs_set(FALSE);
	
	getmaxyx(stdscr,row,col);

	field_w = newwin(row-status_size,col,0,0 );
	status_w = newwin(status_size,col,row-status_size,0 );

	mvwprintw(status_w,1,2,"Client:");
	wrefresh(status_w);





    // draw our borders
 	draw_borders(status_w);
}

//----------------------------------------------------------------------------------

void printLine(WINDOW *win,int startrow,int startcol,int rotation)
{
 int x;
 int r,c;
 int length=4;

switch(rotation){
  case 0:
        for(c=startcol;c<=startcol+length*2+2;c++)
        {

            mvwprintw(win,startrow,c," ");
        }
     break;
  case 90:
     startcol = startcol + length*2+1;
     for(r=startrow;r<=startrow+length;r++)
     {          
        mvwprintw(win,r,startcol,"  ");   
      } 
     break;
  case 180:
     startrow = startrow + length;
     for(c=startcol;c<=startcol+length*2+2;c++)
     {       
        mvwprintw(win,startrow,c," ");    
      } 
     break;
  case 270:
     for(r=startrow;r<=startrow+length;r++)
     {        
        mvwprintw(win,r,startcol,"  ");     
      } 
     break;


  }
}


//----------------------------------------------------------------------------------
void printRectangle(WINDOW *win,int startrow,int startcol)
{
 int r,c; 
 int height = 4;
 int width = 10;

 for(r=startrow;r<=startrow+height;r++)
 {
  for(c=startcol;c<=startcol+width;c++)
  {  
   mvwprintw(win,r,c," ");
  }
 }

}

void printFigure1(WINDOW *win,int startrow,int startcol,int rotation,int colorRectangle, int colorLine){
    wattrset(win,COLOR_PAIR(colorRectangle));
    printRectangle(win,startrow,startcol);
    
    wattrset(win,COLOR_PAIR(colorLine));
    printLine(win,startrow,startcol,rotation);
}


