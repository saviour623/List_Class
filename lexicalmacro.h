#ifndef LEXICAL_MACRO_H
#   define  LEXICAL_MACRO_H

/* TYPE IDENTIFIERS */
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

/* GROUPING OF ARGUMENTS: TELL A FUNCTION TO ITEMIZE ARGUMENTS IN THE GROUP, RATHER THAN CREATING AN ARRAY */


/* expands to group, but we still need to check if type identifier is wrapped in parenthesis, remove the parenthesis and pass the type identifier and arguments to expargs_g_paste */
#define EXPARGS_G(...) \
  IF_ELSE(PARENTHESIS(__VA_ARGS__),  EXPARGS_G_PASTE(EVAL_1 CHOOSE_1(__VA_ARGS__), CHOOSE_VARGS(__VA_ARGS__))) \
    (EXPARGS_G_PASTE(__VA_ARGS__))
/* expargs_g paste: filters out the type identifier from the arguments if provided and paste the arguments */
#define EXPARGS_G_PASTE(...) IF_ELSE(BOOL(IF_VARGS(0, CAT(IDENTIFIER_, CHOOSE_1(__VA_ARGS__))(0))), (__VA_ARGS__)) \
    ((CHOOSE_VARGS(__VA_ARGS__)))

/* check if an argument expands to multiple elements or is va_args */
#define IF_VARGS(...) CHOOSE_2_ARG(__VA_ARGS__,  0)

/* if type identifier is wrapped in parenthesis, unwrap and pass to g_type, else, just pass to g_type */
#define IDENTIFIER_G(ID, ...) IF_ELSE(PARENTHESIS(ID), G_TYPE(EVAL_1 ID))(G_TYPE(ID))

/* we are using if_args as a condition, because if a valid type identifier is provided, identifier_id, where id is the type identifier, should expand to 0, S__(TYPE) which will supply a variable args to if_arg macro */
#define G_TYPE(ID)							\
  IF_ELSE(IF_VARGS(CHOOSE_ARG(CAT(IDENTIFIER_, ID(0)))), S__(G, CAT(T, CHOOSE_2_ARG(CAT(IDENTIFIER_, ID(0)), 0)))) \
    (S__(G, CAT(T, AUTO_TYPE)))
/* read an argument specified as a group, expands to 0, if success */
#define READ_G(...) 0
#define GROUP_ARG(ARG)				\
  IF_ELSE(NOT(CAT(READ_, ARG)), IDENTIFIER_ ## ARG)(0)

#endif/* LEXICAL_MACRO_H */

/* if group type is parenthesized, either handle it or error... maybe handle it
   /* arguments like ARG(a, b) a, b - (a, b) is assumed to be one argument
   /* Group id can be wrapped around parentheesis */
