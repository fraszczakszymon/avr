  #include <stdio.h>
#include <stdlib.h>
#include "queue.h"

void push(int data, struct queue *definedQueue)
{
  definedQueue->queue[++definedQueue->tail] = data;
}

void display(struct queue *definedQueue)
{
  int i;
  for (i=definedQueue->front; i<=definedQueue->tail; i++) {
    if (definedQueue->queue[i] == 0) {
      break;
    }
    printf("%d ", definedQueue->queue[i]);
  }
  printf("\n");
}

void pop(struct queue *definedQueue)
{
  if (definedQueue->front <= definedQueue->tail) {
    definedQueue->queue[definedQueue->front++] = 0;
  }
}