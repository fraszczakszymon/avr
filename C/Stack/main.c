#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

int main()
{
  struct stack *MyStack;
  MyStack = malloc(sizeof(struct stack));
  int tempNum=1;
  MyStack->counter=0;

  while(tempNum!=0) {
    printf("Podaj liczbe: ");
    scanf("%d", &tempNum);
    push(tempNum, MyStack);
  }

  while(MyStack->counter>0) {
    printf("%d", pop(MyStack));
    if (MyStack->counter>0) {
      printf(", ");
    }
  }
  printf("\n\n");

  return 0;
}