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
};

typedef struct figura_struct pFigura;

pFigura* figura_create(int id, int x, int y, int rotation, int colorIn,
        int colorOut, int enable);
int equals(pFigura* t1, pFigura* t2);




#endif   /*FIGURA_H*/