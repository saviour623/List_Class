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
#include "ccl_range.h"
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
  struct genlist *forward_node;
  struct genlist * backward_node;
};

typedef struct Object_List {
  struct genlist *list;
  struct genlist *last; //for now it points at list but "last" will always point to end of node
  struct Object_List *objself;
  char * const loc_obj_name;
  uintmax_t track_items;
  uintptr_t cll_local_address;
  void (*add)(struct Object_List *, void *); //will also assign type
  void (*config_addData)(Object_List *, bool, size_t, size_t, bool, void *);
  void (*remove)(struct Object_List *,  ...);
} cclist_obj_t;

typedef struct objmethod objmethod {
  void (*add)(struct Object_List *, void *);
  void (*config_addData)(Object_List *, bool, size_t, size_t, bool, void *);
  void (*remove)(struct Object_List *,  ...);
};
typedef struct cc_markers cc_markers;
struct cc_markers {
  int8_t memtype;
  int8_t arr_marker;
  int8_t range_marker;
  size_t sizeOf_type;
  size_t numargs;
};

static void logerror(unsigned int signal); /* log error message if debug mode is set */

//TODO: IF GROUP MAKER IN ARRAY, SIGNAL FUNC TO ISOLATE MEMBERS
#define FIND_PAREN_PASS() FIND_PARENTHESIS

/* found parenthesis? move no further */
#define FOUND_PARENTHESIS_1(STATE, ...) ___MOVE_TO_NEXT(1,)
#define FOUND_PARENTHESIS_0(STATE, REM1, ...) ___MOVE_TO_NEXT(STATE, __VA_ARGS__)

#define FIND_PARENTHESIS(STATE, ...)\
  IF_ELSE(CHECK_ARG(__VA_ARGS__), CAT(FOUND_PARENTHESIS_, PARENTHESIS(__VA_ARGS__))(STATE, __VA_ARGS__))\
    (IF_ELSE(CHECK_ARG(CHOOSE_VARGS(__VA_ARGS__)), 2)(STATE))

#define ___MOVE_TO_NEXT(STATE, ...)\
  PUSH(FIND_PAREN_PASS)()(STATE, __VA_ARGS__)

#define ____NOT_ERROR_CODE_2(...) 0

#define catch_paren_or_empty_arg(obj_type, memtype, arr_marker, if_paren_or_single, ...) \
  IF_ELSE(CAT(____NOT_ERROR_CODE_, if_paren_or_single)(0), ____list_expand_param(obj_type, memtype, arr_marker, CAT(paste_va_args_wrapped_unwrapped_, if_paren_or_single)(__VA_ARGS__))) (ASSERT_ARG_0(SIGEMPTY, CHOOSE_ARG(__VA_ARGS__), __VA_ARGS__))

#define paste_va_args_wrapped_unwrapped_0(...) (__VA_ARGS__)
#define paste_va_args_wrapped_unwrapped_1(...) __VA_ARGS__

#define try_dual_choice_expand(cond, prefix, choice_1, choice_2)	\
  CAT(prefix, IF_ELSE(cond, choice_1)(choice_2))

#define clst_macrorep_cT ______clstype
#define clst_macrorep_cP ______clsptr
#define clst_macrorep_cR ______array_clsptr

#define ______clstype(obj_type, ...)\
  __VA_OPT__(catch_paren_or_empty_arg(obj_type, 0, 0, __EXPAND256(FIND_PARENTHESIS(0, __VA_ARGS__)), __VA_ARGS__))

#define ______clsptr(obj_type, ...)\
  __VA_OPT__(catch_paren_or_empty_arg(obj_type, 1, 0, __EXPAND256(FIND_PARENTHESIS(0, __VA_ARGS__)), __VA_ARGS__))

#define ______array_clsptr(obj_type, ...)\
  __VA_OPT__(catch_paren_or_empty_arg(obj_type, 0, 1, __EXPAND256(FIND_PARENTHESIS(0, __VA_ARGS__)), __VA_ARGS__))

#define list(__PREFIX) try_dual_choice_expand(CHECK_ARG(__PREFIX), clst_macrorep_, __PREFIX, cT)

#define ____list_expand_param(obj, memtype, arr_marker, ...)\
  UNLESS(CHECK_ARG(obj))(IF_ELSE(NOT(PARENTHESIS(obj)), CAT(make_redirect_, NOT(PARENTHESIS(obj)))(memtype, obj, arr_marker, __VA_ARGS__)) \
    (UNLESS(CHECK_ARG(__EXPAND1 obj))\
     (IF_ELSE(TEST_FOR_1(NUMAR___G(__EXPAND1 obj)), make_list(memtype, __EXPAND obj, 0, arr_marker, __VA_ARGS__)) \
      (make_list(memtype, SECARG_INEXP((, __EXPAND obj)), IF_ELSE(CHECK_ARG(SECARG_INEXP(obj)), SECARG_INEXP(obj))(0), arr_marker, __VA_ARGS__)))))

/* make_redirect_1: prevents the case where obj is not parenthesized because regardless of the test condition, cpp must expand its macros and an expansion to obj ## token (where obj is parenthesized) will be errornous */
#define make_redirect_1(memtype, obj, grpmaker, ...)  clst_init_list(memtype, obj, 0, grpmaker, __VA_ARGS__)
#define make_list(memtype, obj, type, grpmaker, ...) clst_init_list(memtype, obj, type, grpmaker, __VA_ARGS__)

#define clst_init_list(memtype, obj, type, arr_marker, ...)		\
  typedef ____typeof_unspecified_mem(type, __VA_ARGS__) obj ##_clst_lltype; \
  cclist_obj_t obj; struct objmethod obj ## _method;\
  CAT(if_and_only_if_range_, RANGE_CHECK(ALIAS____(CHOOSE_1, __VA_ARGS__)))\
    (init, obj, memtype, arr_marker, IF_ELSE(type, type)(obj ##_clst_lltype), __VA_ARGS__) \

#define if_and_only_if_range_1(func, obj, memtype, arr_marker, type, rge_arg, ...)\
  range_redirect_init_cc(EXTRACT_RANGE_PARAM(__EXPAND_1 ALIAS____(CHOOSE_2_ARG, __EXPAND_1 rge_arg)), func, obj, memtype, arr_marker, type)
#define range_redirect_init_cc(range_param, ...)\ range_param
  IF_ELSE(PARENTHESIS(range_param), init_macro_construct_cc(__VA_ARGS__, 1, __EXPAND_1 range_param))(ASERT_ARG_)
#define if_and_only_if_range_0(...) ARRAY(__VA_ARGS__)

#define ____typeof_unspecified_mem(type, ...) \
  IF_ELSE(type, type)(IF_ELSE(RANGE_CHECK(CHOOSE_ARG(__VA_ARGS__)), long)\
		      (__typeof__(NULL, ALIAS____(CHOOSE_1, CHOOSE_ARG(__EXPAND_1 __VA_ARGS__)))))

//TODO: init (should have range maker)
#define SECARG_INEXP(INPAREN) ALIAS____(CHOOSE_2_ARG, __EXPAND1 INPAREN)
#define uninitialize(_object)(destroy(&_object))

/* TODO: all erorrs are not working as expected - work on it later on */
#endif /* CLISTPROTO_H */
