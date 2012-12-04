#include <stdio.h>
#include <stdlib.h>
#include "list.h"

void addAtEnd(int data, struct Node **head)
{
  struct Node *temp, *current;
  temp = malloc(sizeof(struct Node));
  // temp = calloc(1, sizeof(struct Node));
  temp->data = data;

  if (*head == NULL) {
    temp->next = NULL;
    *head = temp;
  } else {
    current = *head;
    while (current->next!=NULL) {
      current = current->next;
    }
    temp->next = NULL;
    current->next = temp;
  }
}

void addAtBegin(int data, struct Node **head)
{
  if (*head == NULL) {
    addAtEnd(data, head);
  } else {
    struct Node *temp;
    temp = malloc(sizeof(struct Node));
    temp->data = data;
    temp->next = *head;
    *head = temp;
  }
}

void display(struct Node **head)
{
  struct Node *current;
  current = *head;
  if (current == NULL) {
    printf("List is empty!");
  } else {
    printf("Elements of list: ");
    while (current != NULL) {
      printf("%d ", current->data);
      current = current->next;
    }
    printf("\n");
  }
}

void deleteLast(struct Node **head)
{
  struct Node *current;
  current = *head;
  if (*head != NULL) {
    while (current->next->next != NULL) {
      current = current->next;
    }
    free(current->next);
    current->next = NULL;
  }
}

void deleteFirst(struct Node **head)
{
  if (*head != NULL) {
    struct Node *temp;
    temp = *head;
    *head = temp->next;
    free(temp);
  }
}