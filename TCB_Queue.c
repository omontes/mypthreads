#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "TCBQueue.h"

TCB_queue* TCB_queue_create() {
    TCB_queue* new_queue = (TCB_queue*) malloc(sizeof (TCB_queue));

    if (new_queue == NULL) {
        return NULL;
    } else {
        new_queue->front = NULL;
        new_queue->rear = NULL;
        new_queue->size = 0;
        return new_queue;
    }
}

int TCB_queue_is_empty(TCB_queue* q) {
    return (q->front == NULL && q->rear == NULL);
}

int EnqueueTCB(TCB_queue *q, TCB *t) {
    TCB_queue_node* new_element = (TCB_queue_node*) malloc(sizeof (TCB_queue_node));

    if (new_element == NULL) {
        return ERROR;
    } else {
        new_element->data = t;
        new_element->next = NULL;

        if (TCB_queue_is_empty(q)) {
            q->front = new_element;
            q->rear = new_element;
            q->size++;
        } else {
            (q->rear)->next = (TCB_queue_node*) malloc(sizeof (TCB_queue_node));
            (q->rear)->next = new_element;
            q->rear = (q->rear)->next;
            q->size++;
        }

        return NO_ERROR;
    }
}

TCB* DequeueTCB(TCB_queue* tcb_queue) {
    if (TCB_queue_is_empty(tcb_queue)) {
        return NULL;
    } else if ((tcb_queue->front) == (tcb_queue->rear)) // queue has only one element
    {
        TCB_queue_node* element = tcb_queue->front;

        tcb_queue->front = NULL;
        tcb_queue->rear = NULL;
        tcb_queue->size--;
        return element->data;
    } else {
        TCB_queue_node* element = tcb_queue->front;

        tcb_queue->front = (tcb_queue->front)->next;
        tcb_queue->size--;
        return element->data;
    }
}
