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

// deq_rem_front_update_back(node) goes through the nodes from the back. When
//    the node before the node before the current node doesn't exist, that  
//    means that the previous node is the first one and will be deleted, so 
//    change the pointer
void deq_rem_front_update_back(struct dllnode *node);
void deq_rem_front_update_back(struct dllnode *node) {
  if (node->prev->prev) {
    deq_rem_front_update_back(node->prev);
  } else {
    node->prev = NULL;
  }
}

int dequeue_remove_front(struct dequeue *q) {
  if (q->back->prev == NULL) {
    q->back = NULL;
  } else {
    deq_rem_front_update_back(q->back);
  }
  struct dllnode *backup = q->front;
  int i = q->front->item;
  q->front = q->front->next;
  free(backup);
  return i;
}

// deq_rem_back_update_front(node) goes through the nodes from the front. When
//    the node after the node after the current node doesn't exist, that means 
//    that the next node is the last one and will be deleted, so change the 
//    pointer
void deq_rem_back_update_front(struct dllnode *node);
void deq_rem_back_update_front(struct dllnode *node) {
  if (node->next->next) {
    deq_rem_back_update_front(node->next);
  } else {
    node->next = NULL;
  }
}


int dequeue_remove_back(struct dequeue *q) {
  if (q->front->next == NULL) {
    q->front = NULL;
  } else {
    deq_rem_back_update_front(q->front);
  }
  struct dllnode *backup = q->back;
  int i = q->back->item;
  q->back = q->back->prev;
  free(backup);
  return i;
}

// deq_af_update_back(newnode, first_node) updates the queue so that the last 
//    node on the back contains a pointer to newnode
void deq_add_front_update_back(struct dllnode *newnode, 
                                struct dllnode *last_node);
void deq_add_front_update_back(struct dllnode *newnode, 
                                struct dllnode *last_node){
  if (last_node->prev) {
    deq_add_front_update_back(newnode, last_node->prev);
  } else {
    last_node->prev = newnode;
  }
}

void dequeue_add_front(int item, struct dequeue *q) {
  struct dllnode *newnode = malloc(sizeof(struct dllnode));
  newnode->item = item;
  newnode->next = q->front;
  newnode->prev = NULL;
  q->front = newnode;
  //update the back pointer:
  if(q->back) {
    deq_add_front_update_back(newnode, q->back);
  } else {
    q->back = newnode;
  }
}

// deq_ab_update_front(newnode, first_node) updates the queue so that the last 
//    node on the front contains a pointer to newnode for AddBack
void deq_add_back_update_front(struct dllnode *newnode, 
                               struct dllnode *first_node);
void deq_add_back_update_front(struct dllnode *newnode, 
                               struct dllnode *first_node){
  if (first_node->next) {
    deq_add_back_update_front(newnode, first_node->next);
  } else {
    first_node->next = newnode;
  }
}

void dequeue_add_back(int item, struct dequeue *q){
  struct dllnode *newnode = malloc(sizeof(struct dllnode));
  newnode->item = item;
  newnode->next = NULL;
  newnode->prev = q->back;
  q->back = newnode;
  //update the front pointer:
  if(q->front) {
    deq_add_back_update_front(newnode, q->front);
  } else {
    q->front = newnode;
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
