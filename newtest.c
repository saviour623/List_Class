#include "header.h"
#include <time.h>
#include <stdio.h>
#define start(x) x = clock()
#define stop(x) x = clock() - x
#define print(x) printf("%f\n", x/(double)CLOCKS_PER_SEC)

/* alias */

#define ALIAS____(____MACRO__, ...) ____MACRO__(__VA_ARGS__)

/* creates a static array containing ARG usually base on the type info */
#define DECLARE_CONTENT_ARRAY(ARG, ...) \
  IF_ELSE(AND(LOGICAL_OR(NOT(CAT(READ_, CHOOSE_ARG(__VA_ARGS__))(0)), TEST_FOR_1(CHOOSE_ARG(__VA_ARGS__)))(1), CHECK_ARG(EVAL1 ARG))(1), static __typeof__(0, ALIAS____(CHOOSE_ARG, EVAL_1(EVAL1 ARG))) ____newListobj[] = {EVAL1 ARG};)(static CHOOSE_VARGS(__VA_ARGS__) ____newListobj[] = {EVAL1 ARG};)

/* extracts the important information from the type info, usually group info is (G, (ID, TYPE)) we only need ID and TYPE, also if its not a group. */
#define _____FILTER_ID(...)\
  IF_ELSE(NOT(CAT(READ_, CHOOSE_1(__VA_ARGS__))(0)), ALIAS____(CHOOSE_ARG, EVAL_1(EVAL1 CHOOSE_2_ARG(__VA_ARGS__))), ALIAS____(CHOOSE_VARGS, EVAL_1(EVAL1 CHOOSE_2_ARG(__VA_ARGS__))))(__VA_ARGS__)

#define AB(A, B) A, B
int main(void){
  char *list = "This is my array";
  ARRAY(group, list, G(1, 1, 2, 3));
  return 0;
}
/* #define DECLARE_CONTENT_ARRAY(ARG, ...) - if type info is a group or its an autotype and the members of ARG is non empty create a static array variable using the type of the first member and assign the array to the members of arg. otherwise, create static array variable using the type from type info*/

/** TODO: 1. first argument of ARG cannot be empty
 * 2. We no longer support GENERIC remove it.
 * 3. Every function must take the size of the array.
 */
