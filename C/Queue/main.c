#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

int main()
{
  struct queue *shop;
  int queueSize, i, tempData;
  printf("Set length of queue: ");
  scanf("%d", &queueSize);
  shop = malloc(sizeof(struct queue));
  shop->queue = malloc(queueSize * sizeof(int));
  for (i=0; i<queueSize; i++) {
    shop->queue[i] = 0;
  }
  shop->front = 0;
  shop->tail = -1;

  for (i=0; i<queueSize; i++) {
    printf("Add number: ");
    scanf("%d", &tempData);
    push(tempData, shop);
  }

  display(shop);
  pop(shop);
  display(shop);


  return 0;
}