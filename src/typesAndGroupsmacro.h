#ifndef LEXICAL_MACRO_H
#   define  LEXICAL_MACRO_H

typedef int i32;
typedef long i64;
typedef unsigned int u32;
typedef unsigned long u64;
typedef char * cp__;
typedef float f32;
typedef double f64;

typedef void NO_FUNCTION_PASSED_TO_ARRAY;
/* TYPE IDENTIFIERS */

#define AUTO_TYPE S__(1, 0) /* autotype if type is'nt specified */
#define AUTO PARENTHESIS

#define TS__(ID, ARGTYPE) (ID, ARGTYPE)
#define IDENTIFIER_U(...) 0, S__(2, u32)
#define EXPARGS_U(...) (__VA_ARGS__)
#define IDENTIFIER_I(...) 0, S__(3, i32)
#define EXPARGS_I(...) (__VA_ARGS__)
#define IDENTIFIER_S(...) 0, S__(4, cp__)
#define EXPARGS_S(...) (__VA_ARGS__)
#define IDENTIFIER_D(...) 0, S__(5, f64)
#define EXPARGS_D(...) (__VA_ARGS__)
#define IDENTIFIER_F(...) 0, S__(5, f64)
#define EXPARGS_F(...) (__VA_ARGS__)
#define IDENTIFIER_UL(...) 0, S__(7, u64)
#define EXPARGS_UL(...) (__VA_ARGS__)
#define IDENTIFIER_L(...) 0, S__(8, i64)
#define EXPARGS_L(...) (__VA_ARGS__)
#define IDENTIFIER_C(...) 0, (9, char)
#define EXPARGS_C(...) (__VA_ARGS__)
#define IDENTIFIER_O(...) 0, (10, void *)
#define EXPARGS_O(...) (__VA_ARGS__)
  
#define WRAP_IN_PAREN(ARG, ...)\
  IF_ELSE(PARENTHESIS(ARG), ARG)(WRAP_IN_PAREN_GROUP_AND_TYPE(ARG))
/* cpp would complain for EXPARGS_ ## ARG if ARG is parenthesis, so it's safe to check arguments that aren't parenthesis differently */
#define WRAP_IN_PAREN_GROUP_AND_TYPE(ARG)\
  IF_ELSE(NOT(CAT(READ_, ARG)), EXPARGS_ ## ARG)(IF_ELSE(TYPE(ARG), CAT(EXPARGS_, ARG))(ARG))

/* TYPE SELECTION */
#define TYPE__(...) CHOOSE_2_ARG(__VA_ARGS__, 0)
/* expands to argument's type id if specified */
#define TYPECHECK(ARG, ...)\
  TYPE__(CAT(IDENTIFIER_, ARG))

#define TYPE(ARG, ...)			\
  IF_ELSE(AUTO(ARG), AUTO_TYPE)					\
    (IF_ELSE(TYPECHECK(ARG), TYPECHECK(ARG))(GROUP_ARG(ARG)))

#define EXPARGS_G(...) \
  IF_ELSE(PARENTHESIS(__VA_ARGS__),  EXPARGS_G_PASTE(EVAL_1 CHOOSE_1(__VA_ARGS__), CHOOSE_VARGS(__VA_ARGS__))) \
    (EXPARGS_G_PASTE(__VA_ARGS__))

#define EXPARGS_G_PASTE(...) IF_ELSE(BOOL(IF_VARGS(0, CAT(IDENTIFIER_, CHOOSE_1(__VA_ARGS__))(0))), (__VA_ARGS__)) \
    ((CHOOSE_VARGS(__VA_ARGS__)))

#define IF_VARGS(...) CHOOSE_2_ARG(__VA_ARGS__,  0)

#define IDENTIFIER_G(ID, ...) IF_ELSE(PARENTHESIS(ID), G_TYPE(EVAL_1 ID))(G_TYPE(ID))

#define G_TYPE(ID)							\
  IF_ELSE(IF_VARGS(CHOOSE_ARG(CAT(IDENTIFIER_, ID(0)))), S__(G, CAT(T, CHOOSE_2_ARG(CAT(IDENTIFIER_, ID(0)), 0)))) \
    (S__(G, CAT(T, AUTO_TYPE)))

/* read an argument specified as a group, expands to 0, if success */
#define READ_G(...) 0
#define GROUP_ARG(ARG)				\
  IF_ELSE(NOT(CAT(READ_, ARG)), IDENTIFIER_ ## ARG)(0)

#endif/* LEXICAL_MACRO_H */
