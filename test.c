#include "list-hash_key.h"
#include "array_constructor.h"
#include <time.h>
#include <stdio.h>
#include <stdint.h>
#define start(x) x = clock()
#define stop(x) x = clock() - x
#define print(x) printf("%f\n", x/(double)CLOCKS_PER_SEC)


static void check(char *obj, int type, void *p){
}
int main(void){
  //cT for a C type, cP for pointer, cG for group C type and gP,
  list(cT)((mylist), 'a');

  return 0;
}
//TODO: set a flag for group and a flag for single, so that when ever group is used, single cannot be used
