/* 
 * File:   tserver.h
 * Author: oscar
 *
 * Created on September 20, 2015, 12:30 PM
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <string.h>
#include <pthread.h>
#include <signal.h>
#include "list.h"
#include <unistd.h>
#include <libconfig.h>

#ifndef TSERVER_H
#define	TSERVER_H

#define DELAY 1000000



//lista
pLista* listaFiguras;


//socket

int socket_monitor_1;
int socket_monitor_2;


int open_socket();
int listener(void*sock);

// Serialize
void serialize(pFigura* figura, char* buffer,int monitor_num,int cantidad_columnas);//monitor_num : identificador de cada monitor, inicia en 0

// lista figuras
void initLista();
void agregarFiguraLista(pFigura* figura);
void actualizarFiguraLista(pFigura* figura);
void eliminarFiguraLista(pFigura* figura);

int verificarExisteChoque(pFigura* figura);
int verificarChoqueY(int nueva_posicion_y,pFigura* figura);
int verificarChoqueX(int nueva_posicion_x,pFigura* figura);



// animacion
int asignarMonitor(int xInit);
int isDead(pFigura* figura);
void* pintame();
void elegirSocketEnviarPosicionFigura(pFigura* figura);
int rotacionIncrementalFigura(int angulo);

//lectura cfg
void crearFigurasCFG(void);

#endif	/* TSERVER_H */

