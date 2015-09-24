#include "TCB_list.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

TCB_list* TCB_list_create()
{
	TCB_list* new_list = (TCB_list*)malloc(sizeof(TCB_list));

	if(new_list == NULL)
	{
		return NULL;
	}
	else
	{
		new_list->front = NULL;
		new_list->rear = NULL;
                new_list->size = 0; 
		return new_list;
	}
}

int TCB_list_is_empty(TCB_list* tcb_list)
{
	return (tcb_list->front == NULL && tcb_list->rear == NULL);
}

int TCB_list_add(TCB_list* tcb_list, TCB* tcb)
{
	TCB_list_node* new_node = (TCB_list_node*)malloc(sizeof(TCB_list_node));

	if(new_node == NULL)
	{
		return ERROR;
	}
	else if(tcb_list->rear == NULL) // list is empty
	{
		new_node->data = tcb;

		tcb_list->rear = new_node;
		tcb_list->rear->next = NULL;
		tcb_list->rear->previous = NULL;

		tcb_list->front = new_node;
		tcb_list->front->next = NULL;
		tcb_list->front->previous = NULL;
                
                tcb_list->size++;

		return NO_ERROR;
	}
	else if((tcb_list->front)->next == NULL) // list has only one element
	{
		new_node->data = tcb;

		(tcb_list->front)->next = new_node;
		(tcb_list->rear)->next = new_node;
		new_node->previous = tcb_list->rear;
		new_node->next = NULL;

		tcb_list->rear = (tcb_list->rear)->next;
                tcb_list->size++;
		return NO_ERROR;
	}
	else
	{
		new_node->data = tcb;

		(tcb_list->rear)->next = new_node;
		new_node->previous = tcb_list->rear;
		new_node->next = NULL;

		tcb_list->rear = (tcb_list->rear)->next;
                tcb_list->size++;
		return NO_ERROR;
	}
}

TCB* TCB_list_remove(TCB_list* tcb_list, TCB* tcb)
{
	TCB_list_node* pointer = tcb_list->front;

	while(pointer != NULL)
	{
		if(TCB_equals(pointer->data, tcb))
		{
			TCB_list_node* to_be_removed = pointer;

			if((tcb_list->front)->next == NULL) // list has only one element
			{
				tcb_list->front = NULL;
				tcb_list->rear = NULL;
                                tcb_list->size--;
			}
			else if(pointer->previous == NULL) // list has more than one element and first element is to be removed
			{
				tcb_list->front = (tcb_list->front)->next;
				(tcb_list->front)->previous = NULL;
                                tcb_list->size--;
			}
			else if(pointer->next == NULL) // list has more than one element and last element is to be removed
			{
				(pointer->previous)->next = pointer->next;
				tcb_list->rear = pointer->previous;
                                tcb_list->size--;
			}
			else // default
			{
				(pointer->previous)->next = pointer->next;
				pointer->next->previous = pointer->previous;
                                tcb_list->size--;
			}

			TCB* data = to_be_removed->data;

			free(to_be_removed);

			return data;
		}		
		
		pointer = pointer->next;
	}

	return NULL;
}

int TCB_list_contains(TCB_list* tcb_list, TCB* tcb)
{
	TCB_list_node* pointer = tcb_list->front;

	while(pointer != NULL)
	{
		if(TCB_equals(pointer->data, tcb))
		{
			return NO_ERROR;
		}

		pointer = pointer->next;
	}

	return ERROR;
}

TCB* TCB_list_get(TCB_list* tcb_list, int tid)
{
	TCB_list_node* pointer = tcb_list->front;

	while(pointer != NULL)
	{
		if((pointer->data)->thread_id == tid)
		{
			return (pointer->data);
		}

		pointer = pointer->next;
	}

	return NULL;
}

char* TCB_list_enumerate_tids(TCB_list* tcb_list)
{
	char* tids_string = "";

	TCB_list_node* pointer = tcb_list->front;

	while(pointer != NULL)
	{
		char* s;		
		
		if(strlen(tids_string) == 0) // first number is not preceded by a comma ','
		{
			// memory allocation and string concatenation
			s = malloc(snprintf(NULL, 0, "%s%d", tids_string, (pointer->data)->thread_id) + 1);
			sprintf(s, "%s%d", tids_string, (pointer->data)->thread_id);
		}
		else // starting at second number 'n', we concatenate ",n"
		{
			// memory allocation and string concatenation
			s = malloc(snprintf(NULL, 0, "%s,%d", tids_string, (pointer->data)->thread_id) + 1);
			sprintf(s, "%s,%d", tids_string, (pointer->data)->thread_id);
		}

		tids_string = s;

		pointer = pointer->next;
	}

	return tids_string;
}

char* TCB_list_to_string(TCB_list* tcb_list)
{
	char* TCB_list_string = "";
	
	TCB_list_node* pointer = tcb_list->front;

	while(pointer != NULL)
	{
		char* TCB_string = TCB_to_string(pointer->data);

		if(TCB_string == NULL)
		{
			return NULL;
		}
		else
		{	
			char* s = malloc(snprintf(NULL, 0, "%s %s", TCB_list_string, TCB_string) + 1);
			sprintf(s, "%s %s", TCB_list_string, TCB_string);

			TCB_list_string = s;
		}

		pointer = pointer->next;
	}

	return TCB_list_string;
}

int Print_TCB_list(TCB_list* tcb_list)
{
	char* tcb_list_string = TCB_list_to_string(tcb_list);

	if(tcb_list_string == NULL)
	{
		return ERROR;
	}
	else
	{
		printf("%s",tcb_list_string);
		
		return NO_ERROR;
	}
}

TCB_list* TCB_list_clone(TCB_list* tcb_list)
{
	TCB_list* clone = TCB_list_create();

	TCB_list_node* pointer = tcb_list->front;

	while(pointer != NULL)
	{
		TCB_list_add(clone, pointer->data);

		pointer = pointer->next;
	}
}
