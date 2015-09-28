#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifndef FIGURA_H
#define FIGURA_H

struct figura_struct {
    //Id
    int id;

    //Position
    int x_init;
    int y_init;

   
    //Degrees rotation figure
    int rotation;  //0,90,180,270


    //Color Figure
    int colorIn; 
    int colorOut;
    
    //Enable
    int enable;
    

    double waitTime;
    double lifeTime;
    double tiempoInicio;
    
    int incre_x;
    int incre_y; 
    
    int dirx; 
    int diry; 
    
    int x_final;
    int y_final;
    
     int monitor;
    
    //PARAMETROS DE CONTROL
    double startTime;
    
   
};

typedef struct figura_struct pFigura;

pFigura* figura_create(int id, int x_inicial, int y_inicial, int rotation, int colorIn,
        int colorOut, int enable, double waitTime, int incre_x, int incre_y, int dirx, int diry, int x_final, int y_final, double lifeTime,int monitor);
int equals(pFigura* t1, pFigura* t2);




#endif   /*FIGURA_H*/