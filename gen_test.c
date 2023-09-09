#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>

typedef struct integ integ;
struct integ {
  int data;
  struct integ *link;
};

typedef struct Object {
  struct integ *list;
  struct integ *self;

  void (*add)(struct integ **, int);
} Object;

void init(struct Object *myObject, int data);
void add(integ **self, int data);


void init(struct Object *myObject, int data){
  myObject->list = malloc(sizeof(integ));
  myObject->list->data = data;
  myObject->list->link = NULL;
  myObject->self = myObject->list;
  myObject->add = add;
}
int main(void){
  Object newlist;
  init(&newlist, 1);
  newlist.add(&newlist.self, 2);

  int oo = 0;
  while (oo++ < 15)
    newlist.add(&newlist.self, 3);

  struct integ *ptr = newlist.list;
  while (ptr != NULL){
    printf("%d\n", ptr->data);
    ptr = ptr->link;
    }

  return 0;
}

void add(integ **self, int data){
  struct integ *new_memory = malloc(sizeof(integ));
  new_memory->data = data;
  new_memory->link = NULL;
  (*self)->link = new_memory;
  *self = new_memory;
}
