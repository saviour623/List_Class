#include "utilmacros.h"
#include "typesAndGroupsmacro.h"
#include "numargs.h"
#include "../debug/errormessage.h"

#if __GNUC__
/*#pragma GCC diagnostic ignored "-Wunused-macros"*/
#endif
static char name__[5] = "ARRAY";

/* ARRAY RECURSIVE MACROS */
#define __EXPAND_N_LOOP_IF_ELSE(CONDITION, EXP, ...)	\
    IF_TRUE___EXPAND_AND_REPEAT_ARRAY(CONDITION, EXP, __VA_ARGS__)\
    UNLESS(NOT(CONDITION))
/**/
#define IF_TRUE___EXPAND_AND_REPEAT_ARRAY(CONDITION, EXP, ...)	\
  CAT(SWITCH(CONDITION), CAT(REPEAT_, BOOL(CONDITION)))		\
    (EXP, __VA_ARGS__)

#define HIDE_ARRAY() ARRAY_ARGS
/* recursive */
#define RECALL_ARRAY(FUNC, OBJ, MEMTYPE, TYPE, APPEND_ARGS, ...)__VA_OPT__(;) \
  __VA_OPT__(PUSH(HIDE_ARRAY)()(FUNC, OBJ, MEMTYPE, TYPE, 0, (), __VA_ARGS__))

#define __EXPAND_1REPEAT_1(EXP, ...)			\
  EXP RECALL_ARRAY(__VA_ARGS__)
#define __EXPAND_0REPEAT_0(...)

#define ARRAY(FUNC, OBJ, MEMTYPE, GRPMAKER, ...)				\
  IF_ELSE(PARENTHESIS(OBJ), LOGMSG(SIGOBJPAREN, OBJ))(			\
    CAT(__EXPAND_, NOT(PARENTHESIS(OBJ)))(CAT(__EXPAND_, CHECK_ARG(OBJ)) \
    (__VA_OPT__(IF_ELSE(CHECK_ARG(FUNC), __EXPAND256(ARRAY_ARGS(FUNC, OBJ, MEMTYPE, 1, 0, (), __VA_ARGS__))) \
		((NO_FUNCTION_PASSED_TO_ARRAY)0)))))

/* __ARRAY_ARGS__ */
#define ARRAY_ARGS(FUNC, OBJ, MEMTYPE, TYPE, APPEND_MAKER, APPEND_ARGS, ARG, ...)		\
  __EXPAND_N_LOOP_IF_ELSE(CHECK_ARG(ARG), IF_ELSE(PARENTHESIS(ARG), CAT(ASSERT_ARG_, CHECK_ARG(__EXPAND_1 ARG)) \
       (SIGUNUSED, ARG, CAT(ARG_VARGS_, CHECK_ARG(__EXPAND_1 ARG))\
       (CONSTRUCT_ARRAY(FUNC, OBJ, MEMTYPE, 0, 1, __EXPAND_1 ARG), __VA_ARGS__)))\
			  (ASSERT_ARG_0(SIGBOUND, ARG, __VA_ARGS__)), FUNC, OBJ, MEMTYPE, TYPE, APPEND_MAKER,__VA_ARGS__) \
    (CAT(ASSERT_ARG_, NOT(CHECK_ARG(__VA_ARGS__)))(SIGEMPTY, ","ARG, __VA_ARGS__))

#define CONSTRUCT_ARRAY(FUNC, OBJ, MEMTYPE, GROUP, TYPE, ...) \
  IF_ELSE(NOT(CAT(READ_, ID)(0)), EXPAND_GROUP_PARAM_TO_GROUP(FUNC, OBJ, MEMTYPE, 0, __VA_ARGS__)) \
    (IF_ELSE(TEST_FOR_1(ID),  FUNC(OBJ, MEMTYPE, sizeof int, NUMAR___G(__VA_ARGS__), GROUP, 0, (int[]){__VA_ARGS__})) \
    (FUNC(OBJ, MEMTYPE, sizeof int, NUMAR___G(__VA_ARGS__), GROUP, 0, (int[]){__VA_ARGS__})))

#define EXPAND_GROUP_PARAM_TO_GROUP(FUNC, OBJ, MEMTYPE, TYPE_INFO, ...) \
  GROUP_CONSTRUCTOR(FUNC, OBJ, MEMTYPE, CHOOSE_1 TYPE_INFO, CHOOSE_2_ARG TYPE_INFO, __VA_ARGS__)
#define GROUP_CONSTRUCTOR(FUNC, OBJ, MEMTYPE, ID, STYPE, ...) IF_ELSE(TEST_FOR_1(ID), FUNC(OBJ, MEMTYPE, (0), ID, 1, (0))) \
    (FUNC(OBJ, MEMTYPE, (0), ID, 1, (0)))

//CAT(ASSERT_ARG_, PARENTHESIS(ARG))(SIGBOUND, ARG, CAT(ARG_VARGS_, PARENTHESIS(ARG))
/**
#define MAINT(C, ST, ARG, ...)					\
  IF_ELSE(CHECK_ARG(ARG), CAT(LOOP_, C)(ST, ARG, __VA_ARGS__))(EVAL_1 ST)
#define NEXT(ST, ...) PUSH(PASS)()(1, ST, __VA_ARGS__)

//#define CALLT(...) EVAL8(MAINT(0, (), __VA_ARGS__))
/*if its a group expand continously (9, 6, 7), (9, 5, 6)
first call (9, 6, 7)
second call (9, 6, 7, 9, 6, 6)

main(st_start, st, arg, arg1)    
first - 
main( (), (9, 6, 7), ...)
//if st_start is not 0
   evalmain( (eval st, eval arg)), arg1 )
//
second -
    evalmain( (eval st, eval arg))
 */
