#ifndef _stack_h_
#define _stack_h_

struct stack {
  int counter;
  int array[20];
};

void push(int num, struct stack*);
int pop(struct stack*);

#endif