/* #include "type_macro.h"*/
#include <stdio.h>
//#include "new.h"
#include <stdint.h>
#include "errormessage.h"
//#include "generic.h"

#if __GNUC__
/*#pragma GCC diagnostic ignored "-Wunused-macros"*/
#endif

/* microsoft __va_args__ doesnt expand normally so, TODO: figure out how to bypass it*/
#define SWITCH(val) CONCAT_EXPAND(EVAL_, BOOL(val))
#define EVAL_1(...) __VA_ARGS__
#define EVAL_0(...)
#define CONCAT(st, nd) st ## nd
#define CONCAT_EXPAND(st, nd) CONCAT(st, nd)

#define BOOL(num) CHOOSE_2_ARG(CONCAT(IS_ZERO_, num), 1)
#define CHOOSE_NEXT(_first, _second, ...) _second
#define CHOOSE_2_ARG(...) CHOOSE_NEXT(__VA_ARGS__)
#define IS_ZERO_0 0, 0

/*choose_2_arg helps expand is_zero which normally would act as one argument
concat_expand expands bool(x) which will not expand to its value due to ## */

#define PUSH(BYPASS) BYPASS MISINTERPRET MISINTERPRET MISINTERPRET()()()
#define MISINTERPRET()  /* PARSE NOTHING - SKIPS EXPANSION OF A MACRO */
#define MAIN(ARG1, ARG2, ...)	    	\
  CONCAT_EXPAND(TYPE_SELECT_, NON_EMPTY_VA_ARGS(ARG2))(ARG1, ARG2)	\
    PARSE_TERMINATING_COLON(__VA_ARGS__)	   \
    SWITCH(NON_EMPTY_VA_ARGS(ARG2))		      \
    (PUSH(HIDE_MAIN)()(ARG1, 2, __VA_ARGS__))

#define HIDE_MAIN() MAIN
#define CHOOSE_1(ARG1, ...) ARG1
#define EMPTY_VA_ARGS_(...) 0
#define NON_EMPTY_VA_ARGS(...)\
  BOOL(CHOOSE_1(EMPTY_VA_ARGS_ __VA_ARGS__)())

/*PARSE (;): parse semicolon to an expanded variadic macro (foo();). if macro is empty parse nothing and leave for user to do */
#define  PARSE_TERMINATING_COLON(N, ...)		\
  CONCAT_EXPAND(HAS_ARGUMENT_, NON_EMPTY_VA_ARGS(N))()
#define  HAS_ARGUMENT_1() ;
#define HAS_ARGUMENT_0()

#define EVAL(...) __VA_OPT__(EVAL1024(__VA_ARGS__))
#define EVAL1024(...) __VA_OPT__(EVAL512(EVAL512(__VA_ARGS__)))
#define EVAL512(...) __VA_OPT__(EVAL256(EVAL256(__VA_ARGS__)))
#define EVAL256(...) __VA_OPT__(EVAL128(EVAL128(__VA_ARGS__)))
#define EVAL128(...) __VA_OPT__(EVAL64(EVAL64(__VA_ARGS__)))
#define EVAL64(...) __VA_OPT__(EVAL32(EVAL32(__VA_ARGS__)))
#define EVAL32(...) __VA_OPT__(EVAL16(EVAL16(__VA_ARGS__)))
#define EVAL16(...) __VA_OPT__(EVAL8(EVAL8(__VA_ARGS__)))
#define EVAL8(...) __VA_OPT__(EVAL4(EVAL4(__VA_ARGS__)))
#define EVAL4(...) __VA_OPT__(EVAL2(EVAL2(__VA_ARGS__)))
#define EVAL2(...) __VA_OPT__(EVAL1(EVAL1(__VA_ARGS__)))
#define EVAL1(...) __VA_ARGS__


/*LOGICAL AND */
#define AND(COND1, COND2, ...)\
  CONCAT_EXPAND(SWITCH(COND1), SWITCH(COND2))
#define EVAL_1EVAL_1(...) __VA_ARGS__
#define EVAL_1EVAL_0(...) 0
#define EVAL_0EVAL_1(...) 0
#define EVAL_0EVAL_0(...) 0

/* LOGICAL OR */
#define LOGICAL_OR(COND_1, COND_2) CONCAT_EXPAND(CONCAT_EXPAND(OR_, BOOL(COND_1)), CONCAT_EXPAND(OR_, BOOL(COND_2)))
#define OR_1OR_1(...) __VA_ARGS__
#define OR_1OR_0(...) __VA_ARGS__
#define OR_0OR_1(...) __VA_ARGS__
#define OR_0OR_0(...) 0
/*MAIN CALL */

#define add2element(object, ...)			\
  AND(CHECK_ARG(object), CHECK_ARG(__VA_ARGS__))\
    (EVAL64(MAIN(object, __VA_ARGS__)))

#define T__ TYPE_
#define TYPE_SELECT_1(ARG, ARG2){}

#define TYPE_SELECT_0(...) /*parse nothing */

/* ARRAY SECTION */

#define UNLESS(ARG) \
  CAT(THEN_, BOOL(ARG))
#define THEN_1 EVAL_1
#define THEN_0 EVAL_0

static char name__[5] = "ARRAY";
typedef int i32;
typedef long i64;
typedef unsigned int u32;
typedef unsigned long u64;
typedef char * cp__;
typedef float f32;
typedef double f64;

typedef void NO_FUNCTION_PASSED_TO_ARRAY;
/* TYPE SELECT SCOPE */

#define IF_ELSE(CONDITION, ...)	\
  UNLESS(CONDITION)(__VA_ARGS__)	\
    UNLESS(NOT(CONDITION))

/* autotype is a flag that tells that array type wasnt specified*/
#include "lexicalmacro.h"
#define AUTO_TYPE S__(1, 0)
#define AUTO PARENTHESIS
/* expands specified type to its args, wrapped in parenthesis. If argument ia already a parenthesis, no need to wrap. Wrap for either group or type specified args, else, don't wrap */
#define WRAP_IN_PAREN(ARG, ...)\
  IF_ELSE(PARENTHESIS(ARG), ARG)(WRAP_IN_PAREN_GROUP_AND_TYPE(ARG))
/* cpp would complain for EXPARGS_ ## ARG if ARG is parenthesis, so it's safe to check arguments that aren't parenthesis differently */
#define WRAP_IN_PAREN_GROUP_AND_TYPE(ARG)\
  IF_ELSE(NOT(CAT(READ_, ARG)), EXPARGS_ ## ARG)(IF_ELSE(TYPE(ARG), CAT(EXPARGS_, ARG))(ARG))

#define TYPE__(...) CHOOSE_2_ARG(__VA_ARGS__, 0)
/* expands to argument's type id if specified */
#define TYPECHECK(ARG, ...)\
  TYPE__(CAT(IDENTIFIER_, ARG))

/* parenthesized argument denote autotype (guess type). if type is specified or arguments is a group, create its type info. Anything aside these, is undefined so just pass 0. Undefined type may be asserted in any call that uses types */
#define TYPE(ARG, ...)			\
  IF_ELSE(AUTO(ARG), AUTO_TYPE)					\
    (IF_ELSE(TYPECHECK(ARG), TYPECHECK(ARG))(GROUP_ARG(ARG)))

/* PARENTHESIS SCOPE: test parenthesis. 0 for false, 1 for true */
#define PARENTHESIS(PAREN, ...)				\
  CONCAT_IF_TRUE(PAREN, BOOL(CATCH_EXPAND PAREN), 1)
#define CATCH_EXPAND(...) 0 /* zero, if parenthesis */
#define CAT(a, b) CONCAT_EXPAND(a, b) /* alias */
#define CONCAT_IF_TRUE(PAREN, ARG, ARG1)\
  CAT(CAT(F_, ARG), CAT(F_, ARG1))(PAREN)

#define F_1F_1(...) 0  /* false. not a parenthesis */
#define F_0F_1(...) 1
/*  end scope ... */

/* UNLESS_FALSE: only if false then try other options else true*/
#define UNLESS_FALSE(ARG)\
  CAT(THEN_F, BOOL(ARG))
#define THEN_F0 EVAL_1 /* EVAL_1(...) VA_ARGS: try another opt*/
#define THEN_F1 1 EVAL_0 /* true, no further expansion */

/* checks for argument, including parenthesis */
#define CHECK_ARG(ARG, ...)					\
  UNLESS_FALSE(PARENTHESIS(ARG))(NON_EMPTY_VA_ARGS(ARG))

/* logical NOT */
#define NOT(N)\
  CHOOSE_2_ARG(CAT(NOT_, BOOL(N)), 1)
#define NOT_1 1, 0
/* if 1 expand expression else if 0, log error */
#define ASSERT_ARG_1(SIG, ARG, ...) CHOOSE_1(__VA_ARGS__)
#define ASSERT_ARG_0(SIG, ARG, ...)\
  LOGMSG(SIG, ARG, __VA_ARGS__)
#define CHOOSE_VARGS(ARG, ...) __VA_ARGS__
#define CHOOSE_ARG(ARG, ...) ARG

/* ARRAY, actually creates the array. it asserts the provided arguments given, and call a recursive constructor with a copy of a function, an object, type (assumed from the first argument), the first argument, and the rest, if no error is encountered */
#define ARRAY(FUNC, NAME, OBJ, ...)				\
  SWITCH(PARENTHESIS(OBJ))(LOGMSG(SIGOBJPAREN, OBJ))		\
    CAT(EVAL_, NOT(PARENTHESIS(OBJ)))(CAT(EVAL_, CHECK_ARG(OBJ)) \
    (__VA_OPT__/* ASSERT_OBJ_TYPE(OBJ) */				\
     (IF_ELSE(CHECK_ARG(FUNC), EVAL4(ARRAY_ARGS(FUNC, NAME, OBJ, TYPE(CHOOSE_ARG(__VA_ARGS__)), WRAP_IN_PAREN(__VA_ARGS__), CHOOSE_VARGS(__VA_ARGS__))))	\
     ((NO_FUNCTION_PASSED_TO_ARRAY)0))))

/* expands to __VA_ARGS__ if the condition is true then expands 'else' to EVAL_0 if condition was true, else otherwise */
#define EVAL_N_LOOP_IF_ELSE(CONDITION, EXP, ...)	\
    IF_TRUE_EVAL_AND_REPEAT_ARRAY(CONDITION, EXP, __VA_ARGS__)\
    UNLESS(NOT(CONDITION))
/**/
#define IF_TRUE_EVAL_AND_REPEAT_ARRAY(CONDITION, EXP, ...)	\
  CAT(SWITCH(CONDITION), CAT(REPEAT_, BOOL(CONDITION)))		\
    (EXP, __VA_ARGS__)

#define HIDE_ARRAY() ARRAY_ARGS
/* recursive */
#define RECALL_ARRAY(FUNC, NAME, OBJ, ...)__VA_OPT__(;)			\
  __VA_OPT__(PUSH(HIDE_ARRAY)()(FUNC, NAME, OBJ, TYPE(CHOOSE_ARG(__VA_ARGS__)), WRAP_IN_PAREN(__VA_ARGS__), CHOOSE_VARGS(__VA_ARGS__)))

#define EVAL_1REPEAT_1(EXP, ...)			\
  EXP RECALL_ARRAY(__VA_ARGS__)
#define EVAL_0REPEAT_0(...)

/* ARG_VARGS helps in expansion and error checking. expands to expression, ARG,	\
   when true, else expands to the post arguments for logging error */
#define ARG_VARGS_1(ARG, ...) ARG
#define ARG_VARGS_0(ARG, ...) __VA_ARGS__

  #define ALIAS____(____MACRO__, ...) ____MACRO__(__VA_ARGS__)
//____newListobj
/* creates a static array containing ARG with type usually based on the type info */
#define DECLARE_CONTENT_ARRAY(NAME, ARG, ...)				\
  IF_ELSE(AND(LOGICAL_OR(NOT(CAT(READ_, CHOOSE_ARG(__VA_ARGS__))(0)), TEST_FOR_1(CHOOSE_ARG(__VA_ARGS__)))(1), \
	      CHECK_ARG(EVAL1 ARG))(1), static __typeof__(0, ALIAS____(CHOOSE_ARG, EVAL_1(EVAL1 ARG))) NAME[] = {EVAL1 ARG};)	\
    (static CHOOSE_VARGS(__VA_ARGS__) NAME[] = {EVAL1 ARG};)

/* extracts the important information from the type info, usually group info is (G, (ID, TYPE)) we only need ID and TYPE, also if its not a group. */
#define _____FILTER_ID(...)\
  IF_ELSE(NOT(CAT(READ_, CHOOSE_1(__VA_ARGS__))(0)), ALIAS____(CHOOSE_ARG, EVAL_1(EVAL1 CHOOSE_2_ARG(__VA_ARGS__))),\
	  ALIAS____(CHOOSE_VARGS, EVAL_1(EVAL1 CHOOSE_2_ARG(__VA_ARGS__))))(__VA_ARGS__)

/* array constructor: creates array only if type identifier is valid (non zero), arguments is non empty, and array members is bounded in parenthesis and non empty, if successful, it recursively calls itself with the next argument till all arguments is exhausted */
#define ARRAY_ARGS(FUNC, NAME, OBJ, TYPEID, ARG, ...)			\
  IF_ELSE(LOGICAL_OR(TYPEID, NOT(CHECK_ARG(ARG)))(1),	DECLARE_CONTENT_ARRAY(NAME, ARG, _____FILTER_ID(EVAL_1(EVAL1 CAT(T, TYPEID)))) \
      EVAL_N_LOOP_IF_ELSE(CHECK_ARG(ARG), CAT(ASSERT_ARG_, CHECK_ARG(EVAL_1 ARG)) (SIGUNUSED, ARG, CAT(ARG_VARGS_, CHECK_ARG(EVAL_1 ARG)) \
	(COPY_TOCONSTRUCT(FUNC, NAME, OBJ, CAT(T, TYPEID), ARG), __VA_ARGS__)), FUNC, NAME, OBJ, __VA_ARGS__) \
    (CAT(ASSERT_ARG_, NOT(CHECK_ARG(__VA_ARGS__)))(SIGEMPTY, ","ARG, __VA_ARGS__)) \
  )(LOGMSG(SIGTYPE, ARG, __VA_ARGS__))


//#define CHOOSE_ARG1(ARG1, ...) ARG1

#define TEST_FOR_1(ONE)	NOT(CAT(IS___, ONE))
#define IS___1 0

/* initially the type information and array members were wrapped in parenthesis, so, there's need to expand them to their individual members. */
#define COPY_TOCONSTRUCT(FUNC, NAME, OBJ, TYPE_INFO, ARG)		\
  UNLESS(CHECK_ARG(FUNC))(CONSTRUCT_ARRAY(FUNC, NAME, OBJ, CHOOSE_1 TYPE_INFO, CHOOSE_2_ARG TYPE_INFO, EVAL_1 ARG))

#define CONSTRUCT_ARRAY(FUNC, NAME, OBJ, ID, STYPE, ...)			\
  IF_ELSE(NOT(CAT(READ_, ID)(0)), EXPAND_GROUP_PARAM_TO_GROUP(FUNC, NAME, OBJ, STYPE, __VA_ARGS__)) \
    (IF_ELSE(TEST_FOR_1(ID),  FUNC(OBJ, sizeof NAME / sizeof NAME[0], ID, 0, NAME)) \
     (FUNC(OBJ, sizeof NAME / sizeof NAME[0], ID, 0, NAME)))

/* we must expand the type information before constructing group. first argument of type info is usually the type id and the second is the actual type */
#define EXPAND_GROUP_PARAM_TO_GROUP(FUNC, NAME, OBJ, TYPE_INFO, ...) \
  GROUP_CONSTRUCTOR(FUNC, NAME, OBJ, CHOOSE_1 TYPE_INFO, CHOOSE_2_ARG TYPE_INFO, __VA_ARGS__)
#define GROUP_CONSTRUCTOR(FUNC, NAME, OBJ, ID, STYPE, ...) IF_ELSE(TEST_FOR_1(ID), FUNC(OBJ, sizeof NAME / sizeof NAME[0], ID, 1, NAME)) \
    (FUNC(OBJ, sizeof NAME / sizeof NAME[0], ID, 1, NAME))
