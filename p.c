#include <stdio.h>
#include <stdint.h>

int main(void){
  char *p[] = {"hi", "help"};
  /**
  void *ptr;
  ptr = p;
  uintptr_t intp;
  intp = (uintptr_t)*(uintptr_t **)ptr;
  ptr = (void *)intp;

  printf("%s\n", (char *)ptr);  */

  int i = 256;

  while (i != 0){
    printf("%d,", i);
    i--;
  }
  return 0;
}
