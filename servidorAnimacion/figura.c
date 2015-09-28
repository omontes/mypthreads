#include "figura.h"

pFigura* figura_create(int id, int x, int y, int rotation, int colorIn, 
        int colorOut, int enable, double waitTime, int incre_x, int incre_y, 
        int dirx, int diry, int x_final, int y_final, double lifeTime, int monitor)
{
    pFigura* new_figure = (pFigura*)malloc(sizeof(pFigura));

    if(new_figure == NULL)
    {
        return NULL;
    }
    else
    {
        new_figure->id = id;
        new_figure->x_init = x;
        new_figure->y_init = y;
        new_figure->rotation = rotation;
        new_figure->colorIn = colorIn;
        new_figure->colorOut = colorOut;
        new_figure->enable = enable;
        new_figure->waitTime = waitTime;
        new_figure->incre_x = incre_x;
        new_figure->incre_y = incre_y;
        new_figure->dirx = dirx;
        new_figure->diry = diry;
        new_figure->x_final = x_final;
        new_figure->y_final = y_final;
        new_figure->lifeTime = lifeTime;
        new_figure->monitor = monitor;
        
        
        
        //PARAMETROS DE CONFIGURACION QUE NO SON CONFIGURABLES SINO DE CONTROL
        new_figure->startTime = clock();
        
        
        return new_figure;
    }
}

int equals(pFigura* t1, pFigura* t2)
{
    return (t1->id == t2->id);
}
