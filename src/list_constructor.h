#if __GNUC__
#pragma GCC diagnostic ignored "-Wpedantic"
#pragma GCC diagnostic ignored "-Wunused-macros"
#include "utilmacros.h"
#include "typesAndGroupsmacro.h"
#include "numargs.h"
#include "../debug/errormessage.h"
#endif
/* char name__[5] = "list"; */

#define HIDE_ARRAY() ARRAY_ARGS
/* recursive */

/* if member marks a pointer wrap in {} else dont wrap, recall */
#define MERGE_AND_RECALL_1(FUNC, OBJ, MEMTYPE, ARR_MARKER, TYPE, STATE, ARG, ...)	\
  PUSH(HIDE_ARRAY)()(FUNC, OBJ, MEMTYPE, ARR_MARKER, TYPE, 1, IF_ELSE(ARR_MARKER, (__EXPAND_1 STATE, (TYPE[]){__EXPAND_1 ARG}))((__EXPAND_1 STATE, __EXPAND_1 ARG)), __VA_ARGS__)

#define MERGE_AND_RECALL_0(FUNC, OBJ, MEMTYPE, ARR_MARKER, TYPE, STATE, ARG, ...) \
  PUSH(HIDE_ARRAY)()(FUNC, OBJ, MEMTYPE, ARR_MARKER, TYPE, 1, IF_ELSE(ARR_MARKER, ((TYPE[]){__EXPAND_1 ARG}))(ARG), __VA_ARGS__)

#define RECALL_ARRAY_LL(FUNC, OBJ, MEMTYPE, ARR_MARKER, TYPE, APD, STATE, ARG, ...)\
  CAT(MERGE_AND_RECALL_, BOOL(APD))(FUNC, OBJ, MEMTYPE, ARR_MARKER, TYPE, STATE, ARG, __VA_ARGS__)

#define IF_TRUE_EOR_RCURSE_CLL(...) UNLESS(__VA_ARGS__)
#define ELSE_STOPRCURSE_NEXPD_CLL(...) UNLESS(__VA_ARGS__)
#define ___PUSH_NEXT_CLL_1(___MACRO_CALL) ___MACRO_CALL
#define ___PUSH_NEXT_CLL_0(...)
#define DO_NOTHING_LL(...)

#define ARRAY(FUNC, OBJ, MEMTYPE, ARR_MARKER, TYPE, ...)\
  IF_ELSE(PARENTHESIS(OBJ), LOGMSG(SIGOBJPAREN, OBJ))\
    (CAT(__EXPAND_, NOT(PARENTHESIS(OBJ)))(CAT(__EXPAND_, CHECK_ARG(OBJ))(__VA_OPT__(IF_ELSE(CHECK_ARG(FUNC), __EXPAND256(ARRAY_ARGS(FUNC, OBJ, MEMTYPE, ARR_MARKER, TYPE, 0, (), __VA_ARGS__))) \
		((NO_FUNCTION_PASSED_TO_ARRAY)0)))))

/* __ARRAY_ARGS__ */
#define ARRAY_ARGS(FUNC, OBJ, MEMTYPE, ARR_MARKER, TYPE, APD, STATE, ARG, ...)\
  MAKE_FROM_PARAM_LL((FUNC, OBJ, MEMTYPE, ARR_MARKER, TYPE), APD, STATE, CHECK_ARG(ARG),\
		     PARENTHESIS(ARG), CHECK_ARG(__EXPAND_1 ARG), ARG, __VA_ARGS__)

#define MAKE_FROM_PARAM_LL(PARAM_IN_PAREN, APD, STATE, ARG_ISPRESNT, ARG_ISPAREN, PAREN_NONULL, ARG, ...) \
  IF_TRUE_EOR_RCURSE_CLL(ARG_ISPRESNT)					\
    (IF_ELSE(ARG_ISPAREN, CAT(ASSERT_ARG_, PAREN_NONULL)		\
	     (SIGUNUSED, ARG, CAT(ARG_VARGS_, PAREN_NONULL)(DO_NOTHING_LL(0), __VA_ARGS__)))\
     (ASSERT_ARG_0(SIGBOUND, ARG, __VA_ARGS__))				\
     CAT(___PUSH_NEXT_CLL_, AND(ARG_ISPAREN, PAREN_NONULL)(1))(ALIAS____(RECALL_ARRAY_LL, __EXPAND_1 PARAM_IN_PAREN, APD, STATE, ARG, __VA_ARGS__)))\
    ELSE_STOPRCURSE_NEXPD_CLL(NOT(ARG_ISPRESNT))			\
    (IF_ELSE(NOT(CHECK_ARG(__VA_ARGS__)), ALIAS____(init_macro_construct_cc, __EXPAND_1 PARAM_IN_PAREN, 0, __EXPAND_1 STATE)) \
     (ASSERT_ARG_0(SIGEMPTY, ","ARG, __VA_ARGS__)))

#define init_macro_construct_cc(func, obj, memtype, arr_marker, type, rge_marker, ...) \
  func(&obj, "<list::object>"#obj, (cc_marker){memtype, arr_marker, rge_marker, sizeof IF_ELSE(arr_marker, (type*))((type)), NUMAR___G(__VA_ARGS__)}, (void *) IF_ELSE(arr_marker, (type*[]))((type[])){__VA_ARGS__})
