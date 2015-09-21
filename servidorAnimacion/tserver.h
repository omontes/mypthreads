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
#include "figura.h"

#include <unistd.h>

#ifndef TSERVER_H
#define	TSERVER_H

#define DELAY 1000000


int open_socket();
void* pintame();
int listener(void*sock);


//socket

int socket_monitor_1;
int socket_monitor_2;

// Serialize
void serialize(pFigura* figura, char* buffer);

#endif	/* TSERVER_H */

