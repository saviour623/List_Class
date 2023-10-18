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

//#define PAREN_PAREN_LL(...) PAREN_ABNORMAL_PAREN
/* abnormal parenthesis should continually make zeros if found */
#define PAREN_ABNORMAL_PAREN() 0, PAREN_ABNORMAL_PAREN
/* parenthesis-parenthesis ()() ... is not parenthesis */
//#define FIND_PAREN_PAREN(ARG)					\
  IF_ELSE(NOT(ALIAS____(CHOOSE_ARG, PAREN_PAREN_LL ARG)), 1)(0)

//#define PARENTHESIS(ARG, ...)						\
  IF_ELSE(NOT(FIND_PAREN_PAREN(ARG)), IF_ELSE(CATCH_EXPAND ARG, 0)(1))(0)

#define NUMARGS_256(_256) NOT(CAT(ARGS_8910_, _256))
#define ARGS_8910_256 0

#define NEW_CHECK_ARG(ARG, ...)					\
  IF_ELSE(NOT(FIND_PAREN_PAREN(ARG)), UNLESS_FALSE(PARENTHESIS(ARG))(NON_EMPTY_VA_ARGS(ARG)))(0)

#define EXTRACT_RANGE_PARAM(...)\
  IF_ELSE(CHECK_ARG(__VA_ARGS__), RANGE_SET_BIT(CAT(PRESENT_PARAMETER_JUST_, NUMAR___G(__VA_ARGS__))(__VA_ARGS__)))(error1)

/* present_parameter_just_## 1..3 will set set_bit to 0, meaning cc_range() arguments is in bound, else 1 which is out of bound */
#define RANGE_SET_BIT(...)\
  REDIRECT_RANGE_SET_BIT(__VA_ARGS__)
#define REDIRECT_RANGE_SET_BIT(SET_BIT, ...)\
  IF_ELSE(NOT(SET_BIT), __VA_ARGS__)(error2)

#define PRESENT_PARAMETER_JUST_1(...)				\
  0, (__EXPAND8(NOT_PAREN_NOT_EMPTY((0), 0, __VA_ARGS__)))
#define PRESENT_PARAMETER_JUST_2(...)	\
  0, (__EXPAND8(NOT_PAREN_NOT_EMPTY((0), __VA_ARGS__)))
#define PRESENT_PARAMETER_JUST_3(...)		\
  0, (__EXPAND8(NOT_PAREN_NOT_EMPTY((0), __VA_ARGS__)))

#define NO_EMPTY_NO_PAREN(ARG, ...)		\
  IF_ELSE(AND(CHECK_ARG(ARG), NOT(PARENTHESIS(ARG))), 1)(0)

#define NUMARGS_4(_4) NOT(CAT(ARGS_0123210_, _4))
#define ARGS_0123210_4 0

#define NO_PAREN_TRUE_ARG_1(STATE, ARG, ...)\
  PUSH(HIDE_NOT_PAREN_NOT_EMPTY)()((__EXPAND_1 STATE, ARG), __VA_ARGS__)
#define NO_PAREN_TRUE_ARG_0(STATE, ARG, ...)\
  PUSH(HIDE_NOT_PAREN_NOT_EMPTY)()((__EXPAND_1 STATE, 0), __VA_ARGS__)

#define HIDE_NOT_PAREN_NOT_EMPTY() NOT_PAREN_NOT_EMPTY

/* collects arg if arg isn't empty and not a parenthesis else it replaces the above cases with zeros */
#define NOT_PAREN_NOT_EMPTY(STATE, ARG, ...)		\
  IF_ELSE(NOT(NUMARGS_4(NUMAR___G(__EXPAND_1 STATE))), CAT(NO_PAREN_TRUE_ARG_, AND(NEW_CHECK_ARG(ARG), NOT(PARENTHESIS(ARG)))(1))(STATE, ARG, __VA_ARGS__))(ALIAS____(CHOOSE_VARGS, __EXPAND_1 STATE))


int main(void){
  //  RANGE_CHECK(RANGE);//
  // __EXPAND8(PRESENT_PARAMETER_JUST_2(4, 8))
  EXTRACT_RANGE_PARAM(10)
  return 0;
/* add a self pointer like this:
mylist ## _self

mylist.add(mylist_self, help);

implement splice and slice

*/
//new errors: range value is out of bound, first argument of range cannot be empty
