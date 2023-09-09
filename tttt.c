#include <stdio.h>
#include <math.h>


#define TYPE(FUNC, CT, OBJ, ID, TYPE, ...)			\
 static TYPE de ## CT ## f ## CT ## ___ ## CT[] = {__VA_ARGS__}; FUNC(OBJ, ID, sizeof de ## CT ## f ## CT ## ___ ## CT / sizeof (TYPE), de ## CT ## f ## CT ## ___ ## CT)

#define AUTO_TYPE(FUNC, CT, OBJ, ID, TYPE, ...)			\
  static __typeof__((0, CHOOSE_1(__VA_ARGS__))) de ## CT ## f ## CT ## ___ ## CT[] = {__VA_ARGS__}; FUNC(OBJ, ID, sizeof de ## CT ## f ## CT ## ___ ## CT / sizeof de ## CT ## f ## CT ## ___ ## CT[0], de ## CT ## f ## CT ## ___ ## CT)

#define list(OBJ, ...)\
  __VA_OPT__(AUTO_TYPE(group, 1, 1, 0, 0, __VA_ARGS__))

#define CHOOSE_1(ARG, ...) ARG

int group(int p, int q, size_t r, void *s){
  printf("%zu\n", r);
}
int main(){
  initlist(list);
  /**list_t obj; init(#obj, &obj)
     /* have a flag that tells us if head is empty */

  list(list.self, "hold", "h", "b", "sigh", "be", "please", "yep");
  autolist(list.self, ("hold", "assert"), (1, 2, 3, 5, 8, 12, 6));
  autolist(list.self, S("hold", "assert"), U(1, 2, 3, 5, 8, 12, 6));
  arraylist(list.self, ("parcel", "carriage", "stance"));

  list.add(list.self, "yes");
  list.item(list.self);
  list.join(list.self, new.self);
  list.pop(list.self, index);
  list.push(list.self, data, index);
  list.popinfo(list.self, index);
  list.assigntotype(list.self, type);
  list.sort(list.self); //only for specific type 
  destroylist(mylist);

  assign(index);
  /* would call init with 
  list->add(1, 2);

  //AUTO_TYPE(group, 2, 1, 1, int, 5, 6, 7, 8, 9, 5, 5, 6, 7, 8, 9, 5, 5, 6, 7, 8, 9, 5);

}
