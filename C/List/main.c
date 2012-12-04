#include <stdio.h>
#include "list.h"

int main()
{
  struct Node *head;
  head = NULL;
  addAtBegin(2, &head);
  addAtEnd(3, &head);
  addAtEnd(4, &head);
  addAtEnd(5, &head);
  addAtBegin(1, &head);
  addAtEnd(6, &head);

  display(&head);

  deleteLast(&head);
  display(&head);

  deleteFirst(&head);
  display(&head);

  return 0;
}