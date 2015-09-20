#include "figura.h"

pFigura* figura_create(int id, int x, int y, int rotation, int colorIn, 
        int colorOut, int enable)
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
        return new_figure;
    }
}

int equals(pFigura* t1, pFigura* t2)
{
    return (t1->id == t2->id);
}
