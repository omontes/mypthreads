/*
 * Credits to: https://github.com/marceloprates/uthread
 */
#ifndef TCB_H
#define	TCB_H


#define NO_ERROR 0
#define ERROR -1
#include "ucontext.h"

typedef struct TCB_list_struct TCB_list; // forward declaration
typedef enum {
    READY,
    RUNNING,
    BLOCKED
} State;

struct TCB_struct {
    int thread_id;
    ucontext_t* context;
    State state;
    struct TCB_list_struct* waiting_for_me;
};

typedef struct TCB_struct TCB;

TCB* TCB_create(int thread_id, ucontext_t* context, State state);
int TCB_equals(TCB* t1, TCB* t2);
int TCB_block(TCB* waiting_thread, TCB* blocking_thread);
int TCB_unblock(TCB* waiting_thread, TCB* blocking_thread);
int TCB_is_blocked(TCB* thread);
char* State_to_string(State state);
char* TCB_to_string(TCB* tcb);


#endif	/* TCB_H */

