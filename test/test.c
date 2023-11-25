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
	list()((char_list, char), cc_range('a', 'z'));
	list()(range_list, cc_range(10, 2, -1));

	genlist *p = string_list.list;
	genlist *s = range_list.list;

	/* string */
	while (p != NULL)
	{
		printf("%s ", (string_list_clst_lltype)(p->data));
		p = p->f;
	}
	putchar('\n');

	/* integer */
	while (s != NULL)
	{
		printf("%ld ", *(range_list_clst_lltype *)(s->data));
		s = s->f;
	}
	putchar('\n');

	ccl_remove(&char_list, -1);
	genlist *c = char_list.list;
	/* character */
	while (c != NULL)
	{
		printf("%c ", *(char_list_clst_lltype *)(c->data));
		c = c->f;
	}
	putchar('\n');

	/* pop front */
	printf("first: %s\n", cc_pop_front(string_list));
	printf("first: %ld\n", cc_pop_front(range_list));
	printf("first: %c\n", cc_pop_front(char_list));

	/* pop back */
	printf("back: %s\n", cc_pop_back(string_list));
	printf("back: %ld\n", cc_pop_back(range_list));
	//printf("back: %c\n", cc_pop_back(char_list));

	printf("total: %ld\n", range_list.track_items + string_list.track_items + char_list.track_items);

	/* delete */
//	ccl_delete(range_list.self);
//	ccl_delete(string_list.self);
//	ccl_delete(char_list.self);

	return 0;
}

/* put a marker where array and single cant be used */
