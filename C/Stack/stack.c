#include "stack.h"

void push(int num, struct stack* MyStack)
{
  MyStack->array[MyStack->counter] = num;
  MyStack->counter++;
}

int pop(struct stack* MyStack)
{
  MyStack->counter--;
  return MyStack->array[MyStack->counter];
}