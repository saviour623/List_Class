#ifndef CLISTPROTO_H
#define CLISTPROTO_H

#include <math.h>
#include <stdlib.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdbool.h>
#include "array_constructor.h"

static void addData(Object *objself, bool pointer, size_t sizeofarr, size_t sizeofsingle_entity, bool groupmarker, void *data);
void init(Object_List *object, static const char * nameoflistobj, void *data);
void destroy(Object_List *objself);
static void remfromlist(Object_List *objself, ...);


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
  void (*config_addData)(Object_List *, bool, size_t, size_t, bool, void *);
  void (*remove)(struct Object_List *,  ...);
};
typedef Object_List list;

static void logerror(unsigned int signal); /* log error message if debug mode is set */
typedef enum {
  INT_DATA,
  FLT_DATA
} TYPE;



#define UNUSED(VAR)(void)VAR
//if cc is not space open cc else open cc
#define try_dual_choice_expand(cond, prefix, choice_1, choice_2)	\
  CAT(prefix, IF_ELSE(cond, choice_1)(choice_2))

#define clst_cctype clstype
#define clst_ccptr clsptr
#define clstype(obj, ...) clst_init_list(obj, 0, __VA_ARGS__)
#define clsptr(obj, ...) clst_init_list(obj, 1, __VA_ARGS__)

#define list_select_grp_single_0(obj, memtype, ...)	\
  ARRAY(obj.add, obj, memtype, (__VA_ARGS__))
#define list_select_grp_single_1(obj, memtype, ...)	\
  ARRAY(obj.add, obj, memtype, __VA_ARGS__)

#define list(__PREFIX) try_dual_choice_expand(CHECK_ARG(__PREFIX), clst_, __PREFIX, clstype)
//we check if it is a parenthesis, check if parenhesis has members, check if parenthesis is two argument, check if there is first argument and if there is second argument, if it is not a parenthesis just paste it as obj
#define clst_init_list(obj, memtype, ...)\
  list_t IF_ELSE(PARENTHESIS(obj), CHOOSE_2_ARG(, __EXPAND obj))(obj);\
  //init(&obj, "<list::object>"#obj, _data);				\
  //CAT(list_select_grp_single_, PARENTHESIS(__VA_ARGS__))(obj, memtype,  __VA_ARGS__)
#define ____list_expand_param(memtype, obj, type, ...)

#define oop(obj)\
  IF_ELSE(PARENTHESIS(obj)


#define uninitialize(_object)(destroy(&_object))
#endif /* CLISTPROTO_H */