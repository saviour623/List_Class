#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <time.h>
#include <stdbool.h>
#include <limits.h>
#define start(t) clock_t t = clock()
#define stop(t) (t = clock() - t)
#define print(t) (printf("%f\n", t/(double)CLOCKS_PER_SEC))

struct m_list {
	struct m_list *f;
	struct m_list *b;
	int data;
};

typedef struct {
	struct m_list *l;
	struct m_list *p;
	struct m_list *m;
	int cnt;
} list;

static inline void *allocate_mem(size_t size)
{
	void *memlloc = malloc(size);

	if (memlloc == NULL)
	{
		/* error */
	}
	return memlloc;
}

void l_add(list *obj, int d, int len)
{
	struct m_list *n, **psh;

	obj->cnt += len;
	while ((len--) > 0)
	{
		if ((n = malloc(sizeof (struct m_list))) == NULL)
			abort();
		n->data = d;
		n->f = n->b = NULL;

		if (obj->l == NULL)
		{
			psh = &obj->l;
			obj->p = *psh = n;
			continue;
		}
		n->b = obj->p;
		psh = &obj->p;
		*psh = (*psh)->f = n;
    }
}

#define abs_num(a) ((a) > 0 ? (a) : -(a))
void rng_add(list *__restrict__ obj, int sr, int sp, int st)
{
	struct m_list *n, **psh;
	int abs_st = 0, oo, tmp_st;

	if (st == 0)
		st = 1;

	if ((sr > sp && st > 0) || (sr == sp) || (sr < sp && sp < 0))
		return;

	oo = sp > sr ? sp - abs_num(sr) : sr - abs_num(sp);
	abs_st = abs_num(st);
	tmp_st = st;
	st = 0;

	do {
		oo -= abs_st;
		
		if ((n = malloc(sizeof (struct m_list))) == NULL)
			abort();
		n->data = sr = (sr + st);
		st = tmp_st;
		n->f = n->b = NULL;
		obj->cnt += 1;

		if (obj->l == NULL)
		{
			psh = &obj->l;
			obj->p = *psh = n;
			continue;
		}
		n->b = obj->p;
		psh = &obj->p;
		*psh = (*psh)->f = n;

	} while (oo > 0);
}


void l_delete(list *obj)
{
	struct m_list *n;

	if (obj->l == NULL)
		return;

	while (obj->l != NULL)
	{
		n = obj->l;
		obj->l = obj->l->f;
		free(n);
	}
	obj->p = NULL;
	obj->l = NULL;
}

int main(void){
	list mylist;
	int oo = 0;

	mylist.l = NULL;
	mylist.p = mylist.l;
	mylist.cnt = 0;

	start(k);
	l_add(&mylist, 3, 1000000);
	stop(k);
	print(k);
	
	start(t);
	rng_add(&mylist, 1000000, 0, -3);
	stop(t);
	print(t);

	struct m_list *iter = mylist.l;
	l_delete(&mylist);
	if (iter == NULL)
		printf("yes\n");
	while (iter != NULL)
	{
		printf("%d ", iter->data);
		puts("in");
		break;
		iter = iter->f;
	}
	putchar('\n');
	printf("%d\n", mylist.cnt);
	return 0;
}

/** extend_data(mylist, cc_range(2, 3), cc_splice(4, 6));
 * extend_data(mylist, (1, 3, 4, 6, 8), sort(), cc_splice(4, 6))
 * extend_data(mylist, cc_append(new_list), cc_sort(), cc_reverse())
 * extend_data(mylist, cc_append(), cc_sort(new_data), cc_reverse())
 * extend_data(mylist, cc_append(), cc_sort(), cc_reverse(new_data))
 * in extend data, multuple modes can be combined 
 * if a mode is empty, it seeks input from anothet mode
 * if all mode is empty, they are are all assumed on the list:
 * add, append will be ignored 
 *
 * list(reuse)()
 * when once a list is initiated it does so with a type.
 * if list is REUSED, the initially list is deleted (if non-empty) and a new one with a new type is created. however, a new structure is not created. the old one is used.
 * if no marker or type is provided, list assumes the previous type/marker is assumed.
 * however if type is assumed, a list can only be reused onced. in fact, its not adviceable to reuse with another type

//list(reuse)(mylist, 5, 6, 7, 8, 9, 10);
*/
