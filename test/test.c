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
	list(cP)(string_list, "hello", "this is me");

	list()(range_list, cc_range(100, 2, -2));

	genlist *p = string_list.list;
	genlist *s = range_list.list;

	while (p != NULL)
	{
		printf("%s ", (string_list_clst_lltype)(p->data));
		p = p->f;
	}
	putchar('\n');

	while (s != NULL)
	{
		printf("%ld ", *(range_list_clst_lltype *)(s->data));
		s = s->f;
	}
	putchar('\n');

	printf("total: %ld\n", range_list.track_items);
	ccl_delete(range_list.self);
	ccl_delete(string_list.self);
  return 0;
}

/* put a marker where array and single cant be used */
