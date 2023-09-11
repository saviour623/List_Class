#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct integ integ;
struct integ {
  void *data;
  int type;
  struct integ *link;
};

typedef struct Object Object;
struct Object {
  struct integ *list;
  struct Object *self;
  struct integ *last;
  size_t items;
  void (*add)(struct integ **, void *);
  void (*addData)(Object *, size_t, size_t, _Bool, void *);
};

void init(struct Object *myObject, void * data);
void add(integ **self, void *data);
void addData(Object *, size_t, size_t, _Bool, void *);


void init(struct Object *myObject, void *data){
  myObject->list = malloc(sizeof(integ));
  myObject->list->data = data;
  myObject->list->link = NULL;
  myObject->self = myObject;

  myObject->last = myObject->list;
  myObject->add = add;
  myObject->addData = addData;
}
int main(void){
  Object newlist;
  int testvar = 67;
  int n = 12;
  int arr[] = {1, 2, 4};
  init(&newlist, &n);

  newlist.addData(newlist.self, sizeof arr, sizeof arr[0], 1, arr);

  integ *ptr = newlist.list;
  while (ptr != NULL){
    printf("%d\n", *(int *)ptr->data);
    ptr = ptr->link;
  }
  return 0;
}

void add(integ **self, void *data){
  struct integ *new_memory = malloc(sizeof(integ));
  new_memory->data = data;
  new_memory->link = NULL;
  (*self)->link = new_memory;
  *self = new_memory;
}
void addData(Object *objself, size_t sizeofarr, size_t sizeofsingle_entity, _Bool groupmarker, void *data){
  integ *newMemory = malloc(sizeof(integ));
  integ **point2lastlink;
  if (newMemory == NULL){
    /* corrupted memory/failed allocation */
    // if (DEBUG_MODE)
      //logerror(SIGALLOC);
    abort();
  }
  uintptr_t extractFromVoid __attribute__((unused));
  uintptr_t locatorSkip __attribute__((unused));
  size_t overalsize = sizeofsingle_entity ? sizeofarr / sizeofsingle_entity : 0;


  if (groupmarker == true){
    extractFromVoid = (uintptr_t)data;
    locatorSkip = 0;

    int p = 4;
    while (overalsize != 0) {
      newMemory = malloc(sizeof(integ));
      /* since array has contigious memory, let's assume cache miss is minimal */
      newMemory->data = (void *)(uintptr_t)(extractFromVoid + (locatorSkip ? sizeofsingle_entity * locatorSkip : 0));
      // newMemory->data = (void *)extractFromVoid;
      //newMemory->data = &p;
      newMemory->type = false;
      newMemory->link = NULL;

       point2lastlink = &objself->last;
       (*point2lastlink)->link = newMemory;
       *point2lastlink = newMemory;
       objself->items += 1;

      locatorSkip += 1;
      overalsize -= 1;

    }
    goto end;
  }
  newMemory->data = data;
  newMemory->type = false;
  newMemory->link = NULL;

  point2lastlink = &objself->last;
  (*point2lastlink)->link = newMemory;
  *point2lastlink = newMemory;
  objself->items += 1;

 end: /* Nothing here. End of function */
}
