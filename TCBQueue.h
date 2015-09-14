/* 
 * File:   TCBQueue.h
 * Author: oscar
 *
 * Created on September 10, 2015, 10:25 AM
 */
#ifndef TCB_QUEUE_H
#define	TCB_QUEUE_H
#define NO_ERROR 0
#define ERROR -1
#include "TCB.h"

struct TCB_queue_node_struct {
    struct TCB_struct* data;
    struct TCB_queue_node_struct* next;
};

struct TCB_queue_struct {
    int size;
    struct TCB_queue_node_struct* front;
    struct TCB_queue_node_struct* rear;
};

typedef struct TCB_queue_node_struct TCB_queue_node;
typedef struct TCB_queue_struct TCB_queue;

TCB_queue* TCB_queue_create();
int TCB_queue_is_empty(TCB_queue* tcb_list);
int EnqueueTCB(TCB_queue* tcb_queue, TCB* tcb);
TCB* DequeueTCB(TCB_queue* tcb_queue);
int TCB_queue_contains(TCB_queue* tcb_queue, TCB* tcb);



#endif	/* TCB_QUEUE_H */

