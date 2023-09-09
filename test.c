#include "array_constructor.h"
#include <time.h>
#include <stdio.h>
#define start(x) x = clock()
#define stop(x) x = clock() - x
#define print(x) printf("%f\n", x/(double)CLOCKS_PER_SEC)

#define P(...) __VA_ARGS__
#define STR(OBJ, C, ...) T(group, C, list, 1, int, __VA_ARGS__)
#define lisT(OBJ, ...) STR(OBJ, __COUNTER__, __VA_ARGS__)
void group(char *obj, int size, int type, void *p){
  int *x = p;
  printf("%d\n", *x);
}
#define LETS_TAKE(...) CHOOSE_ARG(__VA_ARGS__)
#define DEFTYPE(TYPEINFO, ARG)\
  AND(LOGICAL_OR(NOT(CAT(READ_, CHOOSE_ARG(EVAL2 T ## TYPEID))), CHOOSE_ARG(EVAL1 T ## TYPEINFO))(1), CHECK_ARG(EVAL1 ARG)) \
    (static __typeof__((void)0, CHOOSE_ARG(EVAL_1 ARG)) ____newListobj;)

static void check(char *obj, int type, void *p){
}
int main(void){
  char *list = "This is my array";
  ARRAY(group, ____newListobj, list, U(1, 2));
  //char *s[] = {"hello", "hi"};
  //printf("%zd\n", sizeof s[0]);

  
  //  DEFTYPE(S__(1, 0), (1, 2, 3))
  // LETS_TAKE(EVAL1 (1, 2, 3))
  //({static int i = 0; });
  //  printf("%d\n", i);
  ///  lisT(list, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11);
  //isT(list, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11);
  //int k[] = {1, 2, 3}
  //P({1, 2, 3})

  //static __auto_type x = (static int[]){1});
  return 0;
}
/*Note curly bracket cannot be found within array */
/**
    The GNU C feature (since version 11) has clear semantics which can be expressed entirely in terms of the adopted typeof feature: the inferred type for a given initializer (init) is, exactly, typeof((0, init))
we could put (void)0*/




  /*IF_TRUE_EVAL_AND_REPEAT_ARRAY(0, 3, 5, 6)
__VA_OPT__(__VA_ARGS__)  //TEST_FOR_1(1)
  //  ARRAY(list, U(3,4), F(1,2), (6, 8, 9));
  //  TYPE_N_ARGS(U(3, 4))
  //  WRAP_IN_PAREN(4)
  //  dummy(U(1, 3))
  //  DUMM(1, 2)
  //  dummy(h, (8,6,6), (8,5,7))*/
/*
  // MACRO_IF_ELSE(CHECK_ARG(), expression, list, 123)(3)
  //UNLESS(1)
  // NOT(1)
  // PARENTHESIS()
  //CHECK_ARG(3) */
