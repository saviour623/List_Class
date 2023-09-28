#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

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
  void (*addData)(Object *, bool, size_t, size_t, bool, void *);
};

void init(struct Object *myObject, void * data);
void add(integ **self, void *data);
static void addData(Object *, bool, size_t, size_t, bool, void *);
void destroy(Object *objself);

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
  int n = 49;
  char *s = "start";
  //char *arr[] = {"hell0", "this", "is", "what i", "was", "talking", "about", "yesterday", "evening"};
  char arr[] = "hello this is a good morning";

  int oo = 0;

  while (oo < strlen(arr)){
    printf("%zu ", (uintptr_t)(arr + oo));
    oo++;
  }
  putchar('\n');
   integ *ptr;
  init(&newlist, &n);
  puts("\n\n");
  newlist.addData(newlist.self, 0, sizeof arr, sizeof arr[0], 1, arr);
  // newlist.addData(newlist.self, sizeof arr, sizeof arr[0], 1, arr);

  ptr = newlist.list; /**
   while (ptr != NULL){
     printf("%c\n", *(char *)ptr->data);
     ptr = ptr->link;
   }
   printf("%c\n", *(char *) newlist.last->data); */
  //destroy(newlist.self);
  return 0;
}
void destroy(Object *objself){
  register uint16_t oo = 0;
  objself->last = objself->list;
  while (objself->last != NULL){
    objself->list = objself->list->link;
    free(objself->last);
    objself->last = objself->list;
  }
  objself->list = NULL;
  //objself->name = "None";
  //objself->items = 0;
  objself->self = NULL;
}
void add(integ **self, void *data){
  struct integ *new_memory = malloc(sizeof(integ));
  new_memory->data = data;
  new_memory->link = NULL;
  (*self)->link = new_memory;
  *self = new_memory;
}
static void addData(Object *objself, bool pointer, size_t sizeofarr, size_t sizeofsingle_entity, bool groupmarker, void *data){
  integ *newMemory, **point2lastlink;
  uintptr_t extractFromVoid __attribute__((unused));
  uintptr_t locatorSkip __attribute__((unused));
  size_t overalsize = sizeofsingle_entity ? sizeofarr / sizeofsingle_entity : 0;

  if (groupmarker == true){
    extractFromVoid = (uintptr_t)data;
    locatorSkip = 0;

    overalsize -= 1;
    while (overalsize != 0) {
      newMemory = malloc(sizeof(integ));
      if (newMemory == NULL){
	abort();
      }
      /* since array has contigious memory, let's assume cache miss is minimal */
      if (pointer == true){
	//newMemory->data = (void *)*(uintptr_t **)(uintptr_t)(extractFromVoid + (uintptr_t)(locatorSkip ? sizeofsingle_entity * locatorSkip : 0));
	printf("%zu ", extractFromVoid + (uintptr_t)(locatorSkip ? sizeofsingle_entity * locatorSkip : 0));
      }
      else {
	//newMemory->data = (void *)(uintptr_t)(extractFromVoid + (locatorSkip ? sizeofsingle_entity * locatorSkip : 0));
	printf("%zu ", extractFromVoid + (uintptr_t)(locatorSkip ? sizeofsingle_entity * locatorSkip : 0));
      }
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
  newMemory = malloc(sizeof(integ));
  if (newMemory == NULL){
    /* corrupted memory/failed allocation */
    // if (DEBUG_MODE)
    //logerror(SIGALLOC);
    abort();
  }
  newMemory->data = data;
  newMemory->type = false;
  newMemory->link = NULL;

  point2lastlink = &objself->last;
  (*point2lastlink)->link = newMemory;
  *point2lastlink = newMemory;
  objself->items += 1;

 end: (void)0; /* Nothing here. End of function */
  putchar('\n');
}
