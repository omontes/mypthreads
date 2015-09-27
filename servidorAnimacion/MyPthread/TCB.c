#include "TCB.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

TCB* TCB_create(int tid, ucontext_t* context, State state, int tipo, int tiquetes) {
    TCB* t = (TCB*) malloc(sizeof (TCB));
    if (t == NULL) {
        return NULL;
    } else {
        t->thread_id = tid;
        t->context = context;
        t->state = state;
        t->tiquetes = tiquetes;
        t->tipo = tipo;        
        t->waiting_for_me = TCB_list_create();
        return t;
    }
}

int TCB_equals(TCB* t1, TCB* t2) {
    return (t1->thread_id == t2->thread_id);
}

int TCB_is_blocked(TCB* thread) {
    return thread->state == BLOCKED;
}

char* State_to_string(State state) {
    char* state_string;
    switch (state) {
        case READY:
            state_string = "ready";
            break;
        case RUNNING:
            state_string = "running";
            break;
        case BLOCKED:
            state_string = "blocked";
            break;
    }

    return state_string;
}

char* TCB_to_string(TCB* tcb)
{
	if(tcb == NULL)
	{
		return NULL;
	}
	else
	{
		int tid = tcb->thread_id;
		State state = tcb->state;
		TCB_list* waiting_for_me = tcb->waiting_for_me;

		char* waiting_for_me_string = TCB_list_enumerate_tids(waiting_for_me);
		
		char* format = "Thread: %d, State: %s, Waiting for me: %s\n";

		// memory allocation and string concatenation
		char* TCB_string = malloc(snprintf(NULL, 0, format, tid, State_to_string(state), waiting_for_me_string) + 1);
		sprintf(TCB_string, format, tid, State_to_string(state), waiting_for_me_string);
		
		return TCB_string;
	}
}


int TCB_block(TCB* waiting_thread, TCB* blocking_thread)
{
	if(blocking_thread == NULL)
	{
		return ERROR;
	}
	else if(waiting_thread == NULL)
	{
		return ERROR;
	}
	else
	{
		TCB_list_add(blocking_thread->waiting_for_me, waiting_thread);

		waiting_thread->state = BLOCKED;

		return NO_ERROR;
	}
}

int TCB_unblock(TCB* waiting_thread, TCB* blocking_thread)
{
	if(blocking_thread == NULL)
	{
		return ERROR;
	}
	else if(waiting_thread == NULL)
	{
		return ERROR;
	}
	else
	{
		TCB_list_remove(blocking_thread->waiting_for_me, waiting_thread);

		waiting_thread->state = READY;

		return NO_ERROR;
	}
}