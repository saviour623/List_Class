#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdbool.h>

int main (){
	char s[8] = "help me";
	void *g = s;
	int oo = 0;
	while (oo++ < 8)
		putchar(*(char *)g++);
}
