/* 
 * File:   tclient.h
 * Author: oscar
 *
 * Created on September 20, 2015, 10:41 AM
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <string.h>
#include <ncurses.h>
#include "list.h"
#ifndef TCLIENT_H
#define	TCLIENT_H

//windows
WINDOW *field_w;
WINDOW *status_w;

pLista* listaFigurasMonitor;



//gcc with lncurses


void initLista();
int verificarEnableFigura(pFigura* figura);
void procesarFiguraEntrante(pFigura* figura);
void pintarFigurasMonitor();
void eliminarFiguraEntrante(pFigura* figura);

//Unserialize
pFigura* unser(pFigura* fig, char* buf);



void show_ncurs();
void draw_borders(WINDOW *screen); 
void printLine(WINDOW *win,int startrow,int startcol,int rotation);                            
void printRectangle(WINDOW *win,int startrow,int startcol); 
void printFigure1(WINDOW *win,int startrow,int startcol,int rotation,int colorRectangle, int colorLine); 


#endif	/* TCLIENT_H */

