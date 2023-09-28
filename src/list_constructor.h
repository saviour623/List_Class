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
#define RECALL_ARRAY(FUNC, OBJ, MEMTYPE, ...)__VA_OPT__(;)		\
  __VA_OPT__(PUSH(HIDE_ARRAY)()(FUNC, OBJ, MEMTYPE, TYPE(CHOOSE_ARG(__VA_ARGS__)), WRAP_IN_PAREN(__VA_ARGS__), CHOOSE_VARGS(__VA_ARGS__)))

#define __EXPAND_1REPEAT_1(EXP, ...)			\
  EXP RECALL_ARRAY(__VA_ARGS__)
#define __EXPAND_0REPEAT_0(...)
#
#
/* creates a static array containing ARG with type usually based on the type info */
#define DECLARE_CONTENT_ARRAY(NAME, ARG, ...) UNLESS(CHECK_ARG(__EXPAND1 ARG)) \
    (IF_ELSE(LOGICAL_OR(NOT(CAT(READ_, CHOOSE_ARG(__VA_ARGS__))(0)), TEST_FOR_1(CHOOSE_ARG(__VA_ARGS__)))(1), static __typeof__(0, CHOOSE_2_ARG(, __EXPAND1 ARG)) NAME[] = {__EXPAND1 ARG};) \
     (static CHOOSE_VARGS(__VA_ARGS__) NAME[] = {__EXPAND1 ARG};))

/* extract the important information from the type info. Usually, group info is (G, (ID, TYPE)) we only need ID and TYPE, also if its not a group.*/
#define _____FILTER_ID(...)\
  IF_ELSE(NOT(CAT(READ_, CHOOSE_1(__VA_ARGS__))(0)), ALIAS____(CHOOSE_ARG, __EXPAND_1(__EXPAND1 CHOOSE_2_ARG(__VA_ARGS__))),\
	  ALIAS____(CHOOSE_VARGS, __EXPAND_1(__EXPAND1 CHOOSE_2_ARG(__VA_ARGS__))))(__VA_ARGS__)

/** __MAIN CONSTRUCTION__: ARRAY & ARRAY_ARGS
 * @ARRAY - Asserts the provided arguments given and call a recursive constructor with the copy of a function, an object, type (assumed from the first
 * argument), the first argument, and the rest, if no error is encountered.
 * @ARRAY_ARGS - creates array only if type identifier is valid (non zero), arguments is non empty, and array members is bounded in parenthesis
 *  and non empty, if successful, it recursively calls itself with the next argument till all variadic arguments is exhausted.
 */
#define ARRAY(FUNC, OBJ, MEMTYPE, ...)				\
  SWITCH(PARENTHESIS(OBJ))(LOGMSG(SIGOBJPAREN, OBJ))		\
    CAT(__EXPAND_, NOT(PARENTHESIS(OBJ)))(CAT(__EXPAND_, CHECK_ARG(OBJ)) \
    (__VA_OPT__/* ASSERT_OBJ_TYPE(OBJ) */				\
     (IF_ELSE(CHECK_ARG(FUNC), __EXPAND4(ARRAY_ARGS(FUNC, OBJ, MEMTYPE, TYPE(CHOOSE_ARG(__VA_ARGS__)), WRAP_IN_PAREN(__VA_ARGS__), CHOOSE_VARGS(__VA_ARGS__)))) \
     ((NO_FUNCTION_PASSED_TO_ARRAY)0))))

/* __ARRAY_ARGS__ */
#define ARRAY_ARGS(FUNC, OBJ, MEMTYPE, TYPEID, ARG, ...)		\
  IF_ELSE(LOGICAL_OR(TYPEID, NOT(CHECK_ARG(ARG)))(1), /* DECLARE_CONTENT_ARRAY(NAME, ARG, _____FILTER_ID(__EXPAND_1(__EXPAND1 CAT(T, TYPEID))))*/ \
	  __EXPAND_N_LOOP_IF_ELSE(CHECK_ARG(ARG), CAT(ASSERT_ARG_, CHECK_ARG(__EXPAND_1 ARG)) (SIGUNUSED, ARG, CAT(ARG_VARGS_, CHECK_ARG(__EXPAND_1 ARG)) (COPY_TOCONSTRUCT(FUNC, OBJ, MEMTYPE, CAT(T, TYPEID), ARG), __VA_ARGS__)), FUNC, OBJ, MEMTYPE, __VA_ARGS__) \
    (CAT(ASSERT_ARG_, NOT(CHECK_ARG(__VA_ARGS__)))(SIGEMPTY, ","ARG, __VA_ARGS__)) \
  )(LOGMSG(SIGTYPE, ARG, __VA_ARGS__))


/* unwraps those arguments iniatially wrapped in parenthesis and calls __construct_array__ to finish up array construction */
#define COPY_TOCONSTRUCT(FUNC, OBJ, MEMTYPE, TYPE_INFO, ARG)		\
  UNLESS(CHECK_ARG(FUNC))(CONSTRUCT_ARRAY(FUNC, OBJ, MEMTYPE, CHOOSE_1 TYPE_INFO, CHOOSE_2_ARG TYPE_INFO, __EXPAND_1 ARG))

#define CONSTRUCT_ARRAY(FUNC, OBJ, MEMTYPE, ID, STYPE, ...)		\
  IF_ELSE(NOT(CAT(READ_, ID)(0)), EXPAND_GROUP_PARAM_TO_GROUP(FUNC, OBJ, MEMTYPE, STYPE, __VA_ARGS__)) \
    (IF_ELSE(TEST_FOR_1(ID),  FUNC(OBJ, MEMTYPE, sizeof int, NUMAR___G(__VA_ARGS__), ID, 0, (int[]){__VA_ARGS__})) \
     (FUNC(OBJ, MEMTYPE, (0), ID, 0, (0))))
//FUNC(OBJ, MEMTYPE, sizeof ((void)0, CHOOSE_1(__VA_ARGS__)), NUMAR___G(__VA_ARGS__), ID, 0, (__typeof__((void)0, CHOOSE_1(__VA_ARGS__))[]){__VA_ARGS__})
/* we must expand the type information before constructing group. first argument of type info is usually the type id and the second is the actual type */
#define EXPAND_GROUP_PARAM_TO_GROUP(FUNC, OBJ, MEMTYPE, TYPE_INFO, ...) \
  GROUP_CONSTRUCTOR(FUNC, OBJ, MEMTYPE, CHOOSE_1 TYPE_INFO, CHOOSE_2_ARG TYPE_INFO, __VA_ARGS__)
#define GROUP_CONSTRUCTOR(FUNC, OBJ, MEMTYPE, ID, STYPE, ...) IF_ELSE(TEST_FOR_1(ID), FUNC(OBJ, MEMTYPE, (0), ID, 1, (0))) \
    (FUNC(OBJ, MEMTYPE, (0), ID, 1, (0)))
