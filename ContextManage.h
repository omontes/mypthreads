
#ifndef CONTEXTMANAGE_H
#define	CONTEXTMANAGE_H
#include "ucontext.h"


ucontext_t* make_context(void *(*function)(void *), void* arg, ucontext_t* link);


#endif	/* CONTEXTMANAGE_H */
