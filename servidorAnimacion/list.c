#include "list.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

pLista* list_create()
{
    pLista* new_list = (pLista*)malloc(sizeof(pLista));

    if(new_list == NULL)
    {
        return NULL;
    }
    else
    {
        new_list->front = NULL;
        new_list->rear = NULL;

        return new_list;
    }
}

int list_is_empty(pLista* lista)
{
    return (lista->front == NULL && lista->rear == NULL);
}

int list_add(pLista* lista, pFigura* figura)
{
    pNodo* new_node = (pNodo*)malloc(sizeof(pNodo));

    if(new_node == NULL)
    {
        return ERROR;
    }
    else if(lista->rear == NULL) // list is empty
    {
        new_node->data = figura;

        lista->rear = new_node;
        lista->rear->next = NULL;
        lista->rear->previous = NULL;

        lista->front = new_node;
        lista->front->next = NULL;
        lista->front->previous = NULL;

        return NO_ERROR;
    }
    else if((lista->front)->next == NULL) // list has only one element
    {
        new_node->data = figura;

        (lista->front)->next = new_node;
        (lista->rear)->next = new_node;
        new_node->previous = lista->rear;
        new_node->next = NULL;

        lista->rear = (lista->rear)->next;

        return NO_ERROR;
    }
    else
    {
        new_node->data = figura;

        (lista->rear)->next = new_node;
        new_node->previous = lista->rear;
        new_node->next = NULL;

        lista->rear = (lista->rear)->next;

        return NO_ERROR;
    }
}

pFigura* list_remove(pLista* lista, pFigura* figura)
{
    pNodo* pointer = lista->front;

    while(pointer != NULL)
    {
        if(equals(pointer->data, figura))
        {
            pNodo* to_be_removed = pointer;

            if((lista->front)->next == NULL) // list has only one element
            {
                lista->front = NULL;
                lista->rear = NULL;
            }
            else if(pointer->previous == NULL) // list has more than one element and first element is to be removed
            {
                lista->front = (lista->front)->next;
                (lista->front)->previous = NULL;
            }
            else if(pointer->next == NULL) // list has more than one element and last element is to be removed
            {
                (pointer->previous)->next = pointer->next;
                lista->rear = pointer->previous;
            }
            else // default
            {
                (pointer->previous)->next = pointer->next;
                pointer->next->previous = pointer->previous;
            }

            pFigura* data = to_be_removed->data;

            free(to_be_removed);

            return data;
        }       
        
        pointer = pointer->next;
    }

    return NULL;
}

int list_contains(pLista* lista, pFigura* figura)
{
    pNodo* pointer = lista->front;

    while(pointer != NULL)
    {
        if(equals(pointer->data, figura))
        {
            return NO_ERROR;
        }

        pointer = pointer->next;
    }

    return ERROR;
}

pFigura* list_get(pLista* lista, int id)
{
    pNodo* pointer = lista->front;

    while(pointer != NULL)
    {
        if((pointer->data)->id == id)
        {
            return (pointer->data);
        }

        pointer = pointer->next;
    }

    return NULL;
}

/*char* list_enumerate_tids(pLista* lista)
{
    char* tids_string = "";

    pNodo* pointer = lista->front;

    while(pointer != NULL)
    {
        char* s;        
        
        if(strlen(tids_string) == 0) // first number is not preceded by a comma ','
        {
            // memory allocation and string concatenation
            s = malloc(snprintf(NULL, 0, "%s%d", tids_string, (pointer->data)->tid) + 1);
            sprintf(s, "%s%d", tids_string, (pointer->data)->tid);
        }
        else // starting at second number 'n', we concatenate ",n"
        {
            // memory allocation and string concatenation
            s = malloc(snprintf(NULL, 0, "%s,%d", tids_string, (pointer->data)->tid) + 1);
            sprintf(s, "%s,%d", tids_string, (pointer->data)->tid);
        }

        tids_string = s;

        pointer = pointer->next;
    }

    return tids_string;
}

*/
/*char* list_to_string(pLista* lista)
{
    char* list_string = "";
    
    pNodo* pointer = lista->front;

    while(pointer != NULL)
    {
        char* string = to_string(pointer->data);

        if(string == NULL)
        {
            return NULL;
        }
        else
        {   
            char* s = malloc(snprintf(NULL, 0, "%s %s", list_string, string) + 1);
            sprintf(s, "%s %s", list_string, string);

            list_string = s;
        }

        pointer = pointer->next;
    }

    return list_string;
}*/

/*int Print_list(pLista* lista)
{
    char* list_string = list_to_string(lista);

    if(list_string == NULL)
    {
        return ERROR;
    }
    else
    {
        printf("%s",list_string);
        
        return NO_ERROR;
    }
}

pLista* list_clone(pLista* lista)
{
    pLista* clone = list_create();

    pNodo* pointer = lista->front;

    while(pointer != NULL)
    {
        list_add(clone, pointer->data);

        pointer = pointer->next;
    }

    return clone;
}

*/