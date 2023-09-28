#include "clistproto.h"

void init(Object_List *object, static const char * nameoflistobj, void *data){
  _object.name = nameoflistobj;
  object->list = malloc(sizeof(list));
  object->list->data = NULL;
  object->list->type = 0;
  object->list->link = NULL;
  object->items = 1;
  object->last = object->list;

  object->objself = object;
   object->config_addData = addData;
  object->remove = remfromlist;
}

void destroy(Object_List *objself){
  register uint16_t oo = 0;
  objself->last = objself->list;
  while (objself->last != NULL){
    objself->list = objself->list->link;
    free(objself->last);
    objself->last = objself->list;
  }
  objself->list = NULL;
  objself->name = "None";
  objself->items = 0;
  objself->objself = NULL;
}

static void addData(Object *objself, bool pointer, size_t sizeofarr, size_t sizeofsingle_entity, bool groupmarker, void *data){
  integ *newMemory, **point2lastlink;
  uintptr_t extractFromVoid __attribute__((unused));
  uintptr_t locatorSkip __attribute__((unused));
  size_t overalsize = sizeofsingle_entity ? sizeofarr / sizeofsingle_entity : 0;

  if (groupmarker == true){
    extractFromVoid = (uintptr_t)data;
    locatorSkip = 0;

    oversize -= 1;
    while (overalsize != 0) {
      newMemory = malloc(sizeof(integ));
      if (newMemory == NULL){
	abort();
      }
      /* since array has contigious memory, let's assume cache miss is minimal */
      if (pointer == true)
	newMemory->data = (void *)*(uintptr_t **)(uintptr_t)(extractFromVoid + (locatorSkip ? sizeofsingle_entity * locatorSkip : 0));
      else
	newMemory->data = (void *)(uintptr_t)(extractFromVoid + (locatorSkip ? sizeofsingle_entity * locatorSkip : 0));
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


#define ____NUMARGS(...) sizeof (unsigned int[]){__VA_ARGS__} / ((sizeof (int)) - 1)

#define remove_data(...)

static void alias_remove_data(Object_List *objself, int numfargs, ...){
  if (numfargs == 0)
    return;
  va_list args;
  va_start(args, numfargs);

  void *forceConvert __attribute__((unused)), **retaiNvoid;
  double dbl_val;  //__attribute__((unused));

  TYPE_DATA(numeric_args_t);
  //PROBLEM: How can data be mapped to  numeric  keys, and predetermine their types since there is no provision for template??
    va_end(args);
}

static void remfromlist(Object_List *objself, ...){
  va_list optionArg;
  va_start(optionArg, objself);

  int index = 1; //what if index is = -1 or negative? what should we do
  genlist *ptr = objself->list;

  if (index == 0){
    objself->list = objself->list->link;
    free(ptr);
    ptr = NULL;
    objself->items -= 1;
    return;
  }

  while (--index)
    ptr = ptr->link;
  genlist *fptr = ptr->link, *nextlinkptr = ptr->link->link;
  ptr->link = nextlinkptr;
  free(fptr);
  fptr = NULL;
  objself->items -= 1;
}

/** modify list(HEAD) without changing the posiion of list(HEAD) pointer, we need a pointer...
      to list(HEAD) but we also want to update list(HEAD), so a double pointer is needed. @objself->last is our pointer and @tmpself is ...*/
