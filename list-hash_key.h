#ifndef GENERIC_LIST
#define GENERIC_LIST

#include <math.h>
#include <stdlib.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>
typedef enum {
  INT_DATA,
  FLT_DATA
} TYPE;
// determine if type is integer or float (1 if true else 0)
#define UNUSED(VAR)(void)VAR
#define list(OBJNAME, ...)\
  list_t OBJNAME;\
  __VA_OPT__(list_initiatize(OBJNAME, sizeof (typeof ((void)0, __VA_ARGS__)[]){__VA_ARGS__} / sizeof typeof ((void)0, __VA_ARGS__), __VA_ARGS__))
#define list_initialize(_object, sizeofdata, _data)	\
  _object.name = "<list::object>"#_object;\
  init(&_object, _data)
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
  char *name;
  uintmax_t items;

  void (*add2list)(struct Object_List *, void *); //will also assign type
  void (*remove)(struct Object_List *,  ...);
};
typedef Object_List list;
#include "generic.h"

void init(Object_List *object, void *data){
  object->list = malloc(sizeof(list));
  object->list->data = data;
  object->list->type = type_check(data);
  object->list->link = NULL;
  object->items = 1;
  object->last = object->list;

  object->objself = object;
  object->add2list = add2list;
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

static void add2list(Object_List *objself, void *data){
  genlist *newMemory = (genlist *)malloc(sizeof(genlist));
  newMemory->data = data;
  newMemory->type = type_check(data) ? 1 : 0;
  newMemory->link = NULL;

  /** modify list(HEAD) without changing the posiion of list(HEAD) pointer, we need a pointer...
      to list(HEAD) but we also want to update list(HEAD), so a double pointer is needed. @objself->last is our pointer and @tmpself is ...*/
  genlist **tmpself = &objself->last;
  (*tmpself)->link = newMemory;
  *tmpself = newMemory;
  objself->items += 1;
}
#define add_data(...)
#include "macro.h"
#include ALIAS_EXEC(function, object, ...)
#define add
#define NUMARGS(...) (sizeof((int[]){__VA_ARGS__})/sizeof(int) - 1)
#define DBLTYPE(_type)(((uintmax_t)cos(M_PI * (double)(_type))))
#define remove_data(...)

static void alias_remove_data(Object_List *objself, int numfargs, ...){
  if (numfargs == 0)
    return;
  va_list args:
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

/***
void print_list(Object_List *self){
  //TODO: print_list should allow user to add specifiers like %(x, o, precision, etc for integers
  //also implement print index function;
  while (list_ptr != NULL){
#     if list_ptr->type == 1;
          typedef int32_t type;
#         define type_spec "d"
#     elif !(list_ptr->type)
#        define type_spec "f"
         typedef double type;
#     else
#       define type_spec "p"
        typedef void * type;
#     endif
  }
  printf(("%") (type_spec), (type *)(self->generic_list->data))
  } */

#endif /* GENERIC_LIST */

/** ADD FEATURES
 * remfromlist
 * (remove a particular value througout the list */
/* remove entire if no index is passed
 *
 * add2list
 * add to index
 * add to last if index is not specified

 * Assign (macro) cast data to appropriate type
 * join
 * join two list with direction eg list 1 first, list 2 second

 * print
 * printf with specification (pass format as string)
 * printf with indexes
 * printf only type (if index is specified print with index)
*/
