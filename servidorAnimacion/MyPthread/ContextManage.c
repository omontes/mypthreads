#include <sys/mman.h>
#include <stdlib.h>
#include <stdio.h>
#include "ContextManage.h"
#define MEMSIZE 10485760

ucontext_t* make_context(void *(*function)(void *), void* arg, ucontext_t* link) {

    ucontext_t* newContext = (ucontext_t*) malloc(sizeof (ucontext_t));

    if (newContext == NULL) {
        return NULL;
    } else {
        getcontext(newContext);
        newContext->uc_link = link;
        newContext->uc_stack.ss_sp = mmap(NULL, MEMSIZE, PROT_WRITE |
                PROT_READ, MAP_PRIVATE | MAP_GROWSDOWN | MAP_ANONYMOUS, -1, 0);
        newContext->uc_stack.ss_size = MEMSIZE;
        newContext->uc_stack.ss_flags = 0;

        makecontext(newContext, (void*) function, 1, arg);

        return newContext;
    }
}

ucontext_t* make_context_noargs(void (*start_routine) (void), ucontext_t* uclink)
{
	ucontext_t* cp = (ucontext_t*)malloc(sizeof(ucontext_t));

	if(cp == NULL)
	{
		return NULL;
	}
	else
	{
		getcontext(cp);
		cp->uc_stack.ss_sp = mmap(NULL,MEMSIZE,
                        PROT_WRITE|PROT_READ,MAP_PRIVATE
                        |MAP_GROWSDOWN|MAP_ANONYMOUS,-1,0);
		cp->uc_stack.ss_size = MEMSIZE;
		cp->uc_link = uclink;

		makecontext(cp, start_routine, 0);

		return cp;
	}
}


