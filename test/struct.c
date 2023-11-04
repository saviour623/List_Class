#include <stdio.h>
#include <stdlib.h>

typedef struct Object_List Object_List;

struct Object_List {
  int items;
  struct *last;
  struct *list;
};

typedef struct list {
  void *data;
  struct list *forward_node;
  struct list *back_node;
};

int main {
  Object_List mainlist;
  mainlist.list = malloc(sizeof (list));
  mainlist.list->forward_node = mainlist.list->back_node = NULL;
  mainlist.last = list;

}
static void addData(Object_List *objself, bool pointer, size_t sizeofarr, bool groupmarker, void *data){
  genlist *newMemory, **point2lastlink;
  char *extractFromVoid __attribute__((unused));
  uintptr_t locatorSkip __attribute__((unused));
  size_t overalsize = sizeofsingle_entity ? sizeofarr / sizeofsingle_entity : 0;

  if (groupmarker == true){
    extractFromVoid = (char *)data;
    locatorSkip = 0;

    overalsize -= 1;
    while (overalsize != 0) {
      newMemory = malloc(sizeof(genlist));
      if (newMemory == NULL){
	abort();
      }
      /* since array has contigious memory, let's assume cache miss is minimal */
   if (pointer == true)
	newMemory->data = (void *)*(char **)(extractFromVoid + (locatorSkip ? sizeofsingle_entity * locatorSkip : 0));
      else
	newMemory->data = (void *)(char *)(extractFromVoid + (locatorSkip ? sizeofsingle_entity * locatorSkip : 0));
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
}
