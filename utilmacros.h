#ifndef _UTILMACROS_
#define _UTILMACROS_
/* ____SWITCH_____ */
#define SWITCH(val) CONCAT_EXPAND(__EXPAND_, BOOL(val))
#define __EXPAND_1(...) __VA_ARGS__
#define __EXPAND_0(...)
#define CONCAT(st, nd) st ## nd
#define CONCAT_EXPAND(st, nd) CONCAT(st, nd)

/* ____BOOL___ */
#define BOOL(num) CHOOSE_2_ARG(CONCAT(IS_ZERO_, num), 1)
#define CHOOSE_NEXT(_first, _second, ...) _second
#define CHOOSE_2_ARG(...) CHOOSE_NEXT(__VA_ARGS__)
#define IS_ZERO_0 0, 0

/* __LOOP__ */
#define PUSH(BYPASS) BYPASS MISINTERPRET MISINTERPRET MISINTERPRET()()()
#define MISINTERPRET()  /* PARSE NOTHING - SKIPS EXPANSION OF A MACRO */

#define __EXPAND(...) __VA_OPT__(__EXPAND1024(__VA_ARGS__))
#define __EXPAND1024(...) __VA_OPT__(__EXPAND512(__EXPAND512(__VA_ARGS__)))
#define __EXPAND512(...) __VA_OPT__(__EXPAND256(__EXPAND256(__VA_ARGS__)))
#define __EXPAND256(...) __VA_OPT__(__EXPAND128(__EXPAND128(__VA_ARGS__)))
#define __EXPAND128(...) __VA_OPT__(__EXPAND64(__EXPAND64(__VA_ARGS__)))
#define __EXPAND64(...) __VA_OPT__(__EXPAND32(__EXPAND32(__VA_ARGS__)))
#define __EXPAND32(...) __VA_OPT__(__EXPAND16(__EXPAND16(__VA_ARGS__)))
#define __EXPAND16(...) __VA_OPT__(__EXPAND8(__EXPAND8(__VA_ARGS__)))
#define __EXPAND8(...) __VA_OPT__(__EXPAND4(__EXPAND4(__VA_ARGS__)))
#define __EXPAND4(...) __VA_OPT__(__EXPAND2(__EXPAND2(__VA_ARGS__)))
#define __EXPAND2(...) __VA_OPT__(__EXPAND1(__EXPAND1(__VA_ARGS__)))
#define __EXPAND1(...) __VA_ARGS__

/*LOGICAL AND */
#define AND(COND1, COND2, ...)\
  CONCAT_EXPAND(SWITCH(COND1), SWITCH(COND2))
#define __EXPAND_1__EXPAND_1(...) __VA_ARGS__
#define __EXPAND_1__EXPAND_0(...) 0
#define __EXPAND_0__EXPAND_1(...) 0
#define __EXPAND_0__EXPAND_0(...) 0

/* LOGICAL OR */
#define LOGICAL_OR(COND_1, COND_2) CONCAT_EXPAND(CONCAT_EXPAND(OR_, BOOL(COND_1)), CONCAT_EXPAND(OR_, BOOL(COND_2)))
#define OR_1OR_1(...) __VA_ARGS__
#define OR_1OR_0(...) __VA_ARGS__
#define OR_0OR_1(...) __VA_ARGS__
#define OR_0OR_0(...) 0

/* LOGICAL NOT */
#define NOT(N)\
  CHOOSE_2_ARG(CAT(NOT_, BOOL(N)), 1)
#define NOT_1 1, 0

/* UNLESS CONDITION THEN EVALUATE - UNLESS(COND)(EXP) */
#define UNLESS(COND) \
  CAT(THEN_, BOOL(COND))
#define THEN_1 __EXPAND_1
#define THEN_0 __EXPAND_0

/* UNLESS_FALSE: only if false then try other options else true*/
#define UNLESS_FALSE(ARG)\
  CAT(THEN_F, BOOL(ARG))
#define THEN_F0 __EXPAND_1
#define THEN_F1 1 __EXPAND_0

/* IF ELSE: THIS CAN BE NESTED - IF_ELSE(COND, IF_EXPRESSION)(ELSE_EXPRESSION) */
#define IF_ELSE(CONDITION, ...)		\
  UNLESS(CONDITION)(__VA_ARGS__)	\
    UNLESS(NOT(CONDITION))

/* __PARENTHESIS__: CHECKS IF AN ARGUMENT IS A PARENTHESIS */
#define PARENTHESIS(PAREN, ...)				\
  CONCAT_IF_TRUE(PAREN, BOOL(CATCH_EXPAND PAREN), 1)
#define CATCH_EXPAND(...) 0 /* zero, if parenthesis */

/* CONCATING MACROS */
#define CONCAT_IF_TRUE(PAREN, ARG, ARG1)\
  CAT(CAT(F_, ARG), CAT(F_, ARG1))(PAREN)
#define F_1F_1(...) 0  /* false. not a parenthesis */
#define F_0F_1(...) 1

#define CAT(A, B) CONCAT_EXPAND(A, B) /* alias for CONCAT_EXPAND */
/* ARGUMENT CHECKING MACROS */
#define NON_EMPTY_VA_ARGS(...)		\
  BOOL(CHOOSE_1(EMPTY_VA_ARGS_ __VA_ARGS__)())
#define EMPTY_VA_ARGS_(...) 0

/*----- __CHECK_ARG__ - CHECKS FOR ARGUMENT, INCLUDING PARENTHESIS */
#define CHECK_ARG(ARG, ...)					\
  UNLESS_FALSE(PARENTHESIS(ARG))(NON_EMPTY_VA_ARGS(ARG))

/* __ALIAS__ - RUNS ANY MACRO PRIVATELY */
#define ALIAS____(____MACRO__, ...) ____MACRO__(__VA_ARGS__)

/* __TEST_FOR_1__ - CHECKS IF AN ARGUMENT IS THE NUMBER "1" */
#define TEST_FOR_1(ONE)	NOT(CAT(IS___, ONE))
#define IS___1 0

/* PASTE TERMINATING COLON */
#define  PARSE_TERMINATING_COLON(N, ...)		\
  CONCAT_EXPAND(HAS_ARGUMENT_, NON_EMPTY_VA_ARGS(N))()
#define  HAS_ARGUMENT_1() ;
#define HAS_ARGUMENT_0()

/* ARGUMENTS SELECTION MACROS */
#define CHOOSE_VARGS(ARG, ...) __VA_ARGS__
#define CHOOSE_ARG(ARG, ...) ARG
#define CHOOSE_1(ARG1, ...) ARG1
#endif /* _UTILMACROS_
