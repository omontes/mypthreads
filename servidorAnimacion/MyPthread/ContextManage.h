/*
 * Credits to: https://github.com/marceloprates/uthread
 */
#ifndef CONTEXTMANAGE_H
#define	CONTEXTMANAGE_H
#include "ucontext.h"


ucontext_t* make_context(void *(*function)(void *), void* arg, ucontext_t* link);
ucontext_t* make_context_noargs(void (*start_routine) (void), ucontext_t* uclink);

#endif	/* CONTEXTMANAGE_H */
