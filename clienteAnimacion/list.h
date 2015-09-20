#include "figura.h"

#ifndef LIST_H
#define LIST_H



#define NO_ERROR 0
#define ERROR -1



struct nodo_struct
{
	struct figura_struct* data;
	struct nodo_struct* previous;
	struct nodo_struct* next;
};

struct list_struct
{
	struct nodo_struct* front;
	struct nodo_struct* rear;
};

typedef struct nodo_struct pNodo;

typedef struct list_struct pLista;

pLista* list_create();
int list_is_empty(pLista* lista);
int list_add(pLista* lista, pFigura* figura);
pFigura* list_remove(pLista* lista, pFigura* figura);
int list_contains(pLista* lista, pFigura* figura);
pFigura* list_get(pLista* lista, int id);
//char* list_enumerate_tids(pLista* lista);
//char* list_to_string(pLista* lista);
//int Print_list(pLista* lista);
//pLista* list_clone(pLista* lista);



#endif   /*LIST_H*/