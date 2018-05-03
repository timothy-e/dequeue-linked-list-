//a Double Ended Queue for ints
// NOTE: ALL double ended queue parameters must be valid

#include "deqll.h"
#include "cs136-tracing.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// DO NOT MODIFY THIS STRUCTURE
struct dllnode {
  int item;
  struct dllnode *prev;
  struct dllnode *next;
};

// DO NOT MODIFY THIS STRUCTURE
struct dequeue {
  struct dllnode *front;
  struct dllnode *back;
};


struct dequeue *dequeue_create(void) {
  struct dequeue *deq = malloc(sizeof(struct dequeue));
  deq->front = NULL;
  deq->back = NULL;
  return deq;
}


bool dequeue_is_empty(const struct dequeue *q) {
  return (q->front == NULL && q->back == NULL);
}


int dequeue_front(const struct dequeue *q) {
  return q->front->item;
}


int dequeue_back(const struct dequeue *q) {
  return q->back->item;
}

int dequeue_remove_front(struct dequeue *q) {
  if (q->front->next) {
    q->front->next->prev = NULL;
  } else {
    q->back = NULL;
  }
  struct dllnode *backup = q->front;
  int i = q->front->item;
  q->front = q->front->next;
  free(backup);
  return i;
}

int dequeue_remove_back(struct dequeue *q) {
  if (q->back->prev) {
    q->back->prev->next = NULL;
  } else {
    q->front = NULL;
  }
  struct dllnode *backup = q->back;
  int i = q->back->item;
  q->back = q->back->prev;
  free(backup);
  return i;
}

void dequeue_add_front(int item, struct dequeue *q) {
  struct dllnode *newnode = malloc(sizeof(struct dllnode));
  newnode->item = item;
  newnode->next = q->front;
  newnode->prev = NULL;
  q->front = newnode;
  if (q->back == NULL) {
    q->back = newnode;
  } else {
    q->front->next->prev = newnode;
  }
}

void dequeue_add_back(int item, struct dequeue *q){
  struct dllnode *newnode = malloc(sizeof(struct dllnode));
  newnode->item = item;
  newnode->next = NULL;
  newnode->prev = q->back;
  q->back = newnode;
  if (q->front == NULL) {
    q->front = newnode;
  } else {
    q->back->prev->next = newnode;
  }
}

void dequeue_destroy(struct dequeue *q) {
  struct dllnode *curnode = q->front;
  struct dllnode *nextnode = NULL;
  while(curnode) {
    nextnode = curnode->next;
    free(curnode);
    curnode = nextnode;
  }
  free(q);
}



// DO NOT MODIFY THIS FUNCTION
// dequeue_print(q) prints the contents of q
// effects: prints to output
void dequeue_print(const struct dequeue *q) {
  struct dllnode *temp = q->front;
  
  printf("Dequeue:\n");
  printf("Front -> ");
  while (temp) {
    printf("%d -> ", temp->item);
    temp = temp->next;
  }
  printf("NULL\n");
  
  temp = q->back;
  printf("Back -> ");
  while (temp) {
    printf("%d -> ", temp->item);
    temp = temp->prev;
  }
  printf("NULL\n");
}
