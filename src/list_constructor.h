#include "utilmacros.h"
#include "typesAndGroupsmacro.h"
#include "numargs.h"
#include "../debug/errormessage.h"

#if __GNUC__
/*#pragma GCC diagnostic ignored "-Wunused-macros"*/
#endif
static char name__[5] = "ARRAY";

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
    (IF_ELSE(NOT(CHECK_ARG(__VA_ARGS__)), ALIAS____(INIT_MACRO_CONSTRUCT, __EXPAND_1 PARAM_IN_PAREN, __EXPAND_1 STATE))\
     (ASSERT_ARG_0(SIGEMPTY, ","ARG, __VA_ARGS__)))

#define INIT_MACRO_CONSTRUCT(FUNC, OBJ, MEMTYPE, ARR_MARKER, TYPE,  ...)\
  FUNC(OBJ.self, "<list::object>"#OBJ, MEMTYPE, ARR_MARKER, (void *)((TYPE[]){__VA_ARGS__}))

//(cast is type if non array type else is type *)

  /* error for () shoud be - arg is either started started with an empty arg or it is empty */
/* use state to make a better error (when not in array style) since it stores the previous arguments to ARRAY */
/* most cases A_1, A_0 is better to prevent double expansion. e.g
   in if(cond, loop1)(loop2): cpp would expand both loop anyways but still use loop1 if condition is true. however, this may cause loop2 to not loop again (if looping method is the same with loop1) when condition is false. so loop ## cond, when condition is true or false would only expand to the specific loop for that condition. */

/* in array bracket shouldn't expand to group type */


/* struct should have a variable that stores its address!
 * init should do the address assigning;
 * destroy should set the variable to 0;
 *

   struct {
   const char * const cll_obj_name;
   const uintptr_t cll_local_address;
   }
   cll_obj_name = #object;
   cll_local_address = (uintptr_t)(uintptr_t *)&object;
 */
