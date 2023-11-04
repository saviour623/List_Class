#include "../src/list-hash_key.h"
#include "../src/list_constructor.h"
#include <time.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#define start(x) x = clock()
#define stop(x) x = clock() - x
#define print(x) printf("%f\n", x/(double)CLOCKS_PER_SEC)

int main(void){
  list()(char_list, ('a', 'a', 'b', 'c', 'd', 'e', 'f'));
  return 0;
}
