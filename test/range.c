//#include "../src/list-hash_key.h"
#include "../src/list_constructor.h"

#define __RANGE_012343210_LL(...) _RANGE_01201_LL
#define _RANGE_01201_LL(...)
#define HIDE_RANGE() RANGE_STATE
#define RANGE(...) \
  (((((((((((((((((((((((__RANGE_012343210_LL)))))))))))))))))))))), (__VA_ARGS__))

#define RANGE_CHECK(ARG) IF_ELSE(PARENTHESIS(ARG), IF_ELSE(PARENTHESIS(ALIAS____(CHOOSE_ARG, __EXPAND_1 ARG)), __EXPAND64(RANGE_STATE((0), ALIAS____(CHOOSE_ARG, __EXPAND_1 ARG))))(0))(0)

#define RANGE_UNTRUE 0

#define RANGE_TRUE_1(STATE, PAREN)\
  PUSH(HIDE_RANGE)()((__EXPAND_1 STATE, 0), __EXPAND_1 PAREN)
#define RANGE_TRUE_0(...) 0

#define RANGE_STATE(STATE, PAREN)\
  IF_ELSE(NOT(NUMPAREN_IS_23(NUMAR___G(__EXPAND_1 STATE))),\
	  CAT(RANGE_TRUE_, PARENTHESIS(PAREN))(STATE, PAREN))\
    (IF_ELSE(AND(NOT(PARENTHESIS(PAREN)), NOT(FIND_PAREN_PAREN(PAREN)))(1), IF_ELSE(NOT(CHECK_ARG(PAREN()())), 1)(0))(0))

#define NUMPAREN_IS_23(VAR_23) NOT(CAT(PAREN_AT_, VAR_23))  
#define PAREN_AT_23 0

#define PAREN_PAREN_LL(...) PAREN_ABNORMAL_PAREN
/* abnormal parenthesis should continually make zeros if found */
#define PAREN_ABNORMAL_PAREN() 0, PAREN_ABNORMAL_PAREN
/* parenthesis-parenthesis ()() ... is not parenthesis */
#define FIND_PAREN_PAREN(ARG)\
  IF_ELSE(NOT(ALIAS____(CHOOSE_ARG, PAREN_PAREN_LL ARG)), 1)(0)

#define PARENTHESIS(ARG, ...) \
  IF_ELSE(NOT(FIND_PAREN_PAREN(ARG)), IF_ELSE(CATCH_EXPAND ARG, 0)(1))(0)

#define NUMARGS_256(_256) NOT(CAT(ARGS_8910_, _256))
#define ARGS_8910_256 0

#define NEW_CHECK_ARG(ARG, ...)					\
  IF_ELSE(NOT(FIND_PAREN_PAREN(ARG)), UNLESS_FALSE(PARENTHESIS(ARG))(NON_EMPTY_VA_ARGS(ARG)))(0)

int main(void){
  RANGE_CHECK(RANGE);
  return 0;
}

/* add a self pointer like this:
mylist ## _self

mylist.add(mylist_self, help);

implement splice and slice

*/
