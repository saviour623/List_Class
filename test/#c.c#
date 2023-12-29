#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdbool.h>
#include "../src/clistproto.h"
#undef list
#define __builtin_assert_ptype(T)\
	(__builtin_classify_type((T)0) == __builtin_classify_type((void *)0))
#define _BUFFER(type, n)\
	(__builtin_assert_ptype(type) ? (void *)((type *[(n)]){0}) : (void *)((type [(n)]){0}))

#define list(obj, ...)							\
	do {\
		if (! __builtin_types_compatible_p(__typeof__(obj), Object_List)) return 0; \
		if (! CHOOSE_ARG(1 __VA_OPT__(,) - 1)) { abort(); __builtin_unreachable(); } \
		typedef __typeof__ ((void)0, CHOOSE_ARG(__VA_OPT__(__VA_ARGS__,) (void)0)) obj ## _clst_lltype; \
		listp(&obj, #obj, (cc_marker){__builtin_assert_ptype(obj ## _clst_lltype), \
					0, 0, sizeof (obj ## _clst_lltype), NUMAR___G(__VA_ARGS__)}, \
			(void *)(_BUFFER(obj ## _clst_lltype, NUMAR___G(__VA_ARGS__))) __VA_OPT__(, __VA_ARGS__)); \
	} while (0)

void listp(Object_List *obj, char *obj_name, cc_marker marker, void *buffer, ...)
{
	if (obj == NULL)
		return;

	puts(obj_name);
}

void *abc(char **j)
{
	*j = "h";
	j[1] = "e";
	j[2] = "l";
	j[3] = "l";
	j[4] = "o";
	j[5] = NULL;

	return j;
}
int main(){
	Object_List obj;
	list(obj, 1);
	char **j = abc((char *[6]){0});

	while (*j != NULL)
	{
		puts(*j);
		j++;
	}
	printf("%d\n", __builtin_classify_type((void *)0));
	_BUFFER(int, 6);
	__builtin_assert_ptype(int);
}
