#ifndef _list_h_
#define _list_h_

struct Node {
  int data;
  struct Node* next;
};

void addAtEnd(int, struct Node**);
void addAtBegin(int, struct Node**);
void display(struct Node**);
void deleteLast(struct Node**);
void deleteFirst(struct Node**);

#endif