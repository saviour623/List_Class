#include "../src/list-hash_key.h"
#include "../src/list_constructor.h"
#include <time.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#define start(x) x = clock()
#define stop(x) x = clock() - x
#define print(x) printf("%f\n", x/(double)CLOCKS_PER_SEC)


static void check(char * self){
  //list(repl)(char, self);
}
int main(void){
  //cT for a C type, cP for pointer, cG for group C type and gP for group pointer,
  //ARRAY(add, mylist, 0, 0, int, (1, 2), (3, 4));
  //__EXPAND 1, 2 3
  list()(mylist, (65), ('a', 'b'), ('c', 'd'), ('e', 'f'));
  //list()((mylist, int), 5, (65, 91), ('a', 'b'), ('c', 'd'), ('e', 'f'));

  //pop_front(mylist); -> ((mylist_clslltype)(mylist.pop(mylist.self)))
  //create_struct(mylist, char);
  // list()((mylist, int), ('a', 'b', 'c', 'd', 'e', 'f', 'g', 'i', 'j'));
  /**
  list()((mylist, int), range(10, 2));
  assuming it works this way

  mylist_method.add(mylist.self, data);
  mylist_method.pop(mylist.self, data);
  pop_front(mylist); // ((mylist ## _clslltype)(mylist.pop(mylist.self)))
  pop_back(mylist);
  mylist_method.iterate(mylist.self, 5); */
  return 0;
}
//TODO: set a flag for group and a flag for single, so that when ever group is used, single cannot be used
//ARRAY(func, obj, memtype, "hello")

//
