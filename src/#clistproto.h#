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
#include "list_constructor.h"
/**
#if UINTPTR_T
#define uintptr uintmax_t
#endif
*/
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

struct ObjectSelf {
  struct genlist *list;
  struct genlist *last;
  struct ObjectSelf *objself;
  const char * const name;

  void (*add)(struct Object_List *, void *);
  void (*config_addData)(Object_List *, bool, size_t, size_t, bool, void *);
  void (*remove)(struct Object_List *,  ...);
};

typedef struct objmethod objmethod {
  void (*add)(struct Object_List *, void *);
  void (*config_addData)(Object_List *, bool, size_t, size_t, bool, void *);
  void (*remove)(struct Object_List *,  ...);
}
/**
#define create_struct(self, type_st_object)		\
  static struct self ## obj_ ## defclass  {							\
    type_st_object type_llist_object;					\
    size_t st_offsetof_memoObj;						\
    const char * const selfName;						\
    uintmax_t items;							\
    ObjectSelf *self;							\
    } self, *self_track=&self; objmethod self ## _method ; */
//REMEMBER - when initializing, i will also initialize self_method
//#define init(self)
typedef Object_List list;

static void logerror(unsigned int signal); /* log error message if debug mode is set */

//TODO: IF GROUP MAKER IN ARRAY, SIGNAL FUNC TO ISOLATE MEMBERS

#define try_dual_choice_expand(cond, prefix, choice_1, choice_2)	\
  CAT(prefix, IF_ELSE(cond, choice_1)(choice_2))

#define clst_macrorep_cT ______clstype
#define clst_macrorep_cP ______clsptr
#define clist_macrorep_cG ______clstype
#define clist_macrorep_gP ______group_clsptr
#define ______clstype(obj, ...) ____list_expand_param(obj, 0, 0, __VA_ARGS__)
#define ______clsptr(obj, ...) ____list_expand_param(obj, 1, 0, __VA_ARGS__)
#define ______group_clsptr(obj, ...) ____list_expand_param(obj, 0, 1, __VA_ARGS__)

#define list_select_grp_single_0(obj, memtype, grpmaker, ...)	\
  ARRAY(obj.add, obj, memtype, grpmaker, (__VA_ARGS__))
#define list_select_grp_single_1(obj, memtype, grpmaker, ...)	\
  ARRAY(obj.add, obj, memtype, grpmaker, __VA_ARGS__)

#define list(__PREFIX) try_dual_choice_expand(CHECK_ARG(__PREFIX), clst_macrorep_, __PREFIX, cT)

/* make_redirect_1: prevents the case where obj is not parenthesized, regardless of the condition, an expansion to obj ## token will be errornous */
#define make_redirect_1(memtype, obj, grpmaker, ...)  clst_init_list(memtype, obj, 0, grpmaker, __VA_ARGS__)
#define ____list_expand_param(obj, memtype, grpmaker, ...)\
  UNLESS(CHECK_ARG(obj))(IF_ELSE(NOT(PARENTHESIS(obj)), CAT(make_redirect_, NOT(PARENTHESIS(obj)))(memtype, obj, grpmaker, __VA_ARGS__)) \
    (UNLESS(CHECK_ARG(__EXPAND1 obj))\
     (IF_ELSE(TEST_FOR_1(NUMAR___G(__EXPAND1 obj)), make_list(memtype, __EXPAND obj, 0, grpmaker, __VA_ARGS__)) \
      (make_list(memtype, CHOOSE_ARG(__EXPAND obj), IF_ELSE(CHECK_ARG(SECARG_INEXP(obj)), SECARG_INEXP(obj))(0), grpmaker, __VA_ARGS__)))))

#define make_list(memtype, obj, type, grpmaker, ...) clst_init_list(memtype, obj, type, grpmaker, __VA_ARGS__)

#define clst_init_list(memtype, obj, type, grpmaker, ...)\
  create_struct(obj, type)					\
  init(&obj, "<list::object>"#obj, _data);				\
  CAT(list_select_grp_single_, PARENTHESIS(__VA_ARGS__))(obj, memtype, grpmaker, __VA_ARGS__)

#define SECARG_INEXP(INPAREN) ALIAS____(CHOOSE_2_ARG, __EXPAND1 INPAREN)
#define uninitialize(_object)(destroy(&_object))

#endif /* CLISTPROTO_H */
