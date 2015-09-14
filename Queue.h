/* 
 * File:   Queue.h
 * Author: oscar
 *
 * Created on September 10, 2015, 10:30 AM
 */
#ifndef QUEUE_H
#define	QUEUE_H
#include<ucontext.h>

/*Queue has five properties. capacity stands for the maximum number of elements Queue can hold.
  Size stands for the current size of the Queue and elements is the array of elements. front is the
 index of first element (the index at which we remove the element) and rear is the index of last element
 (the index at which we insert the element) */
typedef struct Queue {
    int capacity;
    int size;
    int front;
    int rear;
    ucontext_t *elements;
} Queue;


Queue * createQueue(int maxElements);
void Dequeue(Queue *Q);
ucontext_t front(Queue *Q);
ucontext_t Enqueue(Queue *Q, ucontext_t element);

#endif	/* QUEUE_H */

