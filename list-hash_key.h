
#ifndef GENERIC_LIST
#define GENERIC_LIST

#include <math.h>
#include <stdlib.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdbool.h>
#include "array_constructor.h"

typedef enum {
  INT_DATA,
  FLT_DATA
} TYPE;
// determine if type is integer or float (1 if true else 0)
static void logerror(unsigned int signal); /* log error message if debug mode is set */

#define UNUSED(VAR)(void)VAR
#define list(OBJNAME, ...)\
  static list_t OBJNAME;\
  init(&_object, "<list::object>"#_object, _data);\
  __VA_OPT__(IF_ELSE(PARENTHESIS(__VA_ARGS__)), ARRAY(OBJECTNAME.add, __initobjmem, OBJECTNAME, __VA_ARGS__)\
	     (ARRAY(OBJECTNAME.add, __initobjmem, OBJECTNAME, (__VA_ARGS__))))

#define uninitialize(_object)(destroy(&_object))

#define type_check(_type)(int)pow(((int)cosl(M_PI * (float)*(double*)(_type))), 2)
typedef struct genlist genlist;
typedef struct Object_List Object_List;

struct genlist {
  void *data;
  int16_t type;
  struct genlist *link;
};

struct Object_List {
  struct genlist *list;
  struct genlist *last; //for now it points at list but "last" will always point to end of node
  struct Object_List *objself;
  const char * const name;
  static uintmax_t items;

  void (*add)(struct Object_List *, void *); //will also assign type
  void (*remove)(struct Object_List *,  ...);
};
typedef Object_List list;
#include "generic.h"
void init(Object_List *object, static const char * nameoflistobj, void *data){
  _object.name = nameoflistobj;
  object->list = malloc(sizeof(list));
  object->list->data = NULL;
  object->list->type = 0;
  object->list->link = NULL;
  object->items = 1;
  object->last = object->list;

  object->objself = object;
  object->add = addData;
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

[[noreturn]] static void addData(Object_List *objself, size_t sizeofarr, size_t sizeofsingle_entity, _Bool groupmarker, void *data){
  genlist *newMemory = malloc(sizeof(genlist));
  genlist **point2lastlink;
  if (newMemory == NULL){
    /* corrupted memory/failed allocation */
    if (DEBUG_MODE)
      logerror(SIGALLOC);
    abort();
  }
  uintptr_t extractFromVoid __attribute__((unused));
  uintptr locatorSkip __attribute__((unused));
  size_t overalsize = sizeofarr / sizeofsingle_entity;

  if (groupmarker == true){
    extractFromVoid = (uintptr_t)data;
    locatorSkip = 0;

    do {
      /* since array has contigious memory, let's assume cache miss is minimal */
      newMemory->data = (void *)(uintptr_t)(extractFromVoid | (sizeofsingle_entity << locatorSkip));
      newMemory->type = false;
      NewMemory->link = NULL;

       point2lastlink = &objself->last;
       (*point2lastlink)->link = newMemory;
       *point2lastlink = newMemory;
       objself->items += 1;

      locatorSkip += 1;
      overalsize -= 1;

    } while (!oversize);
    !oversize ? goto end : 0;
  }
  newMemory->data = data;
  newMemory->type = false;
  NewMemory->link = NULL;

  point2lastlink = &objself->last;
  (*point2lastlink)->link = newMemory;
  *point2lastlink = newMemory;
  objself->items += 1;

 end: /* Nothing here. End of function */
}

#define ____NUMARGS(...) sizeof (unsigned int[]){__VA_ARGS__} / ((sizeof (int)) - 1)

#define DBLTYPE(_type)(((uintmax_t)cos(M_PI * (double)(_type))))

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
