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

#define clst_clstype clstype
#define clst_clsptr clsptr
#define clstype(obj, ...) ____list_expand_param(obj, 0, __VA_ARGS__)
#define clsptr(obj, ...) ____list_expand_param(obj, 1, __VA_ARGS__)

#define list_select_grp_single_0(obj, memtype, ...)	\
  ARRAY(obj.add, obj, memtype, (__VA_ARGS__))
#define list_select_grp_single_1(obj, memtype, ...)	\
  ARRAY(obj.add, obj, memtype, __VA_ARGS__)

#define list(__PREFIX) try_dual_choice_expand(CHECK_ARG(__PREFIX), clst_, __PREFIX, clstype)

#define ____list_expand_param(obj, memtype, ...)\
  UNLESS(CHECK_ARG(obj))(IF_ELSE(NOT(PARENTHESIS(obj)), make_list(memtype, obj, 0, __VA_ARGS__)) \
    (UNLESS(CHECK_ARG(__EXPAND obj))\
     (IF_ELSE(TEST_FOR_1(NUMAR___G(__EXPAND obj)), make_list(memtype, __EXPAND obj, 0, __VA_ARGS__)) \
      (make_list(memtype, SECARG_INEXP((, __EXPAND obj)), IF_ELSE(CHECK_ARG(SECARG_INEXP(obj)), SECARG_INEXP(obj))(0), __VA_ARGS__)))))

#define make_list(memtype, obj, type, ...) clst_init_list(memtype, obj, type, __VA_ARGS__)

#define clst_init_list(memtype, obj, type, ...)\
  list_t obj; init(&obj, "<list::object>"#obj, _data);		\
  CAT(list_select_grp_single_, PARENTHESIS(__VA_ARGS__))(obj, memtype,  __VA_ARGS__)

  //IF_ELSE(CHECK_ARG(CHOOSE_2_ARG(__EXPAND obj)), clst_init_list(memtype, obj, CHOOSE_2_ARG(__EXPAND obj), __VA_ARGS__))(clst_init_list(memtype, obj, 0, __VA_ARGS__)))
#define SECARG_INEXP(INPAREN) ALIAS____(CHOOSE_2_ARG, __EXPAND INPAREN)
#define uninitialize(_object)(destroy(&_object))
#endif /* CLISTPROTO_H */
