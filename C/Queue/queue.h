#ifndef _queue_
#define _queue_

struct queue {
  int *queue;
  int front, tail;
};

void push(int, struct queue*);
void display(struct queue*);
void pop(struct queue*);

#endif