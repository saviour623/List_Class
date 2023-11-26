#include <stdio.h>

int main (){
	char s[8] = "help me";
	void *g = s;
	int oo = 0;
	while (oo++ < 8)
		putchar(*(char *)g++);
}
