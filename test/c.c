#include <stdio.h>

int i = 56;
int main (){
extern int i;
  printf("%d\n", i);
}
