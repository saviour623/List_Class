#include "../src/list-hash_key.h"
#include "../src/list_constructor.h"
#include <time.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#define start(x) clock_t x = clock()
#define stop(x) x = clock() - x
#define print(x) printf("%f\n", x/(double)CLOCKS_PER_SEC)

int main(void){
	list(cP)(range_list, "hello", "this is me");
	cc_marker mark = {.numargs = 2, .memtype = 1, .sizeOf_type = sizeof (0, "hello")};
//	long x = 5;
	char *hello = "hello";
	char *s[2];
	s[0] = "hello";
	s[1] = "hope";

	void *ptr = s;

	//	printf("%s, %s\n", *(char **)ptr, *(char **)ptr+8);
//	list()(range_list, cc_range(10, 2, -2));
	//ccl_add_init(range_list.self, s, mark);

	genlist *p = range_list.list;

	while (p != NULL)
	{
		printf("%s\n", (range_list_clst_lltype)(p->data));
		p = p->f;
	}
	printf("total: %ld\n", range_list.track_items);
	ccl_delete(range_list.self);
  return 0;
}

/* put a marker where array and single cant be used */
