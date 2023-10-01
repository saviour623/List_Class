#include "../src/list-hash_key.h"
#include "../src/list_constructor.h"
#include <time.h>
#include <stdio.h>
#include <stdint.h>
#define start(x) x = clock()
#define stop(x) x = clock() - x
#define print(x) printf("%f\n", x/(double)CLOCKS_PER_SEC)


static void check(ObjectSelf * self){
  list(repl)(char, self);
}
int main(void){
  //cT for a C type, cP for pointer, cG for group C type and gP for group pointer,



  //create_struct(mylist, char);
  // list()((mylist, int), ('a', 'b', 'c', 'd', 'e', 'f', 'g', 'i', 'j'));

  list()((mylist, int), range(10, -1));
  /* assuming it works this way */
#define create_list()\
  typedef char mylist_clslltype;\
  struct Object_class mylist; struct objmethod self ## _method;

  mylist_method.add(mylist.self, data);
  mylist_method.pop(mylist.self, data);
  pop_front(mylist); // ((mylist ## _clslltype)(mylist.pop(mylist.self)))
  mylist_method.iterate(mylist.self);
  return 0;
}
//TODO: set a flag for group and a flag for single, so that when ever group is used, single cannot be used
//ARRAY(func, obj, memtype, "hello")

//
