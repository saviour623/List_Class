#include "header.h"
#include <stdio.h>
#include <stdint.h>

#define MISS()
#define PUSHT(m) m MISS MISS MISS()()()
#define PASS() MAINT

#define LOOP_1(ST, ARG, ...)\
  NEXT((EVAL_1 ST, EVAL_1 ARG), __VA_ARGS__)
#define LOOP_0(ST, ARG, ...) NEXT(ARG, __VA_ARGS__)

#define MAINT(C, ST, ARG, ...)					\
  IF_ELSE(CHECK_ARG(ARG), CAT(LOOP_, C)(ST, ARG, __VA_ARGS__))(EVAL_1 ST)
#define NEXT(ST, ...) PUSH(PASS)()(1, ST, __VA_ARGS__)

//#define CALLT(...) EVAL8(MAINT(0, (), __VA_ARGS__))
/*if its a group expand continously (9, 6, 7), (9, 5, 6)
first call (9, 6, 7)
second call (9, 6, 7, 9, 6, 6)

main(st_start, st, arg, arg1)    
first - 
main( (), (9, 6, 7), ...)
//if st_start is not 0
   evalmain( (eval st, eval arg)), arg1 )
//
second -
    evalmain( (eval st, eval arg))
 */
int pp(uintptr_t *k){
  printf("%u\n", (uintptr_t)k); 
}
  int main(){
    EVAL8(MAINT(0, (), (1, 2, 3, 4), (2, 4, 6, 8), (801, 456, 235, 356, 599, 256, 345, 125, 456), (4570, 35567, 3456)))
}


//TODO: check if list has a pointer memeber but list(cP) wasnt specified
//have a pointer to that always adjust to the middle of list, so that iteration can be easier. check if iterate is less or greater than middle - check if iterator is closer to middle or beginning by halving the middle, then iterate either from begining upward or middle downward OR iterate from middle upward or end downward.

//for group - paste the values and form one compound literal. e.g
//(1, 2, 3), (4, 5, 6) = (type[]){1, 2, 3, 4, 5, 6}
//for array - paste each values inside {} and form one array compound literal
// (1, 2, 3), (4, 5, 6) = (type*[]){{1, 2, 3}, {4, 5, 6}}
