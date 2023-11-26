#ifndef CCL_LIST_H
#define CCL_LIST_H
#include "clistproto.h"

#define __UNUSED__ __attribute__((unused))
#define cc_pop_front(object)							\
	(*(object ## _clst_lltype *)ccl_pop(object.self, 0))
#define cc_pop_back(object)							\
	(*(object ## _clst_lltype *)ccl_pop(object.self, -1))

void *ccl_pop(Object_List *obj, long index)
{
	if (obj->list == NULL || obj->list->data == NULL)
		error_routine(ERRNULL);
	if ( !(index) )
		return obj->pointer_mem ? (void *)&obj->list->data : obj->list->data;
	if (index == -1)
		return obj->pointer_mem ? (void *)&obj->last->data : obj->last->data;
	return NULL;
}

void init(Object_List *object, char * const obj_name, cc_marker marker, void *data)
{
	object->loc_obj_name = obj_name;

	object->list = object->last = NULL;
	object->track_items = 0;

	if (marker.range_marker)
		ccl_range(object, *(long *)data, ((long *)data)[1], ((long *)data)[2]);
	else
		ccl_add_init(object, data, marker);

	object->pointer_mem = marker.memtype;
	object->self = object;
	object->cll_local_address = (uintptr_t)(object->self);
}


#define abs_num(a) ((a) > 0 ? (a) : -(a))
void ccl_range(Object_List *__restrict__ obj, long start, long stop, long step)
{
	struct genlist *n, **ptr_last;
	int abs_st = 0, oo, tmp_st;

	if (step == 0)
		step = 1;

	if ((start > stop && step > 0) || (start == stop) || (start < stop && stop < 0))
		return;

	oo = abs_num(stop - start);
	abs_st = abs_num(step);
	tmp_st = step;
	step = 0;

	do {
		oo -= abs_st;

		if ((n = malloc(sizeof (struct genlist))) == NULL)
			error_routine(ERRMEM);
		n->range_tmp = start = (start + step);
		n->data = &n->range_tmp;
		step = tmp_st;
		n->f = n->b = NULL;
		obj->track_items += 1;

		if (obj->list == NULL)
		{
			ptr_last = &obj->list;
			obj->last = *ptr_last = n;
			continue;
		}
		n->b = obj->last;
		ptr_last = &obj->last;
		*ptr_last = (*ptr_last)->f = n;

	} while (oo > 0);
}

__UNUSED__ static void ccl_add_init(Object_List *obj, void *data, cc_marker info)
{
	struct genlist *n, **ptr_last;
	size_t skip, sizeof_skip, len;

	obj->track_items += info.numargs;
	len = info.numargs;
	skip = 0;

	while ((len--) > 0)
	{
		sizeof_skip = info.sizeOf_type * skip;

		if ((n = malloc(sizeof (struct genlist))) == NULL)
			error_routine(ERRMEM);

		n->data = info.memtype ? *(unsigned char **)((char *)data + sizeof_skip) : (unsigned char *)data + sizeof_skip;
		n->f = n->b = NULL;
		skip += 1;

		if (obj->list == NULL)
		{
			ptr_last = &obj->list;
			obj->last = *ptr_last = n;
			continue;
		}
		n->b = obj->last;
		ptr_last = &obj->last;
		*ptr_last = (*ptr_last)->f = n;
	}
}

__attribute__((nonnull)) void ccl_remove(Object_List *obj, int which)
{
	genlist *ptr = obj->list, **tmp __UNUSED__;

	if (ptr == NULL)
		error_routine(0 /*warning attempting to remove from an empty list */);
	if (which < 0)
		which = obj->track_items + which;
	if (which > obj->track_items || which < 0)
		error_routine(0/* seeked index cannot be found */);

	--obj->track_items;
	if (which == 0){
		obj->list = obj->list->f;
		obj->list->b = NULL;
		goto free;
	}
	else if (which == obj->track_items)
	{
		ptr = obj->last;
		obj->last = obj->last->b;
		obj->last->f = NULL;
		goto free;
	}
	while (which-- && (ptr = ptr->f))
		;
	tmp = &ptr;
	(*tmp)->b->f = (*tmp)->f;
free:
	free(ptr);
	ptr = NULL;
}

#define __CCL_TYPEOF__(d) (__typeof__(((void)0, d)))
#define __CCL_SIZEOF__(d) (__sizeof__(((void)0, d)))
#define LIST_SIZE_MAX 256
#define cc_slice(obj, s, e, d)									\
	slice(obj, s, e, __CCL_SIZEOF__(d), (__CCL_TYPEOF__(d)[LIST_SIZE_MAX]){data});

//!(x < LIST_SIZE_MAX) ? ((typeof (data)[x])(data)) : malloc(sizeof (data) * size);
void slice(Object_List *obj, int sl_s, int sl_e, size_t siz, void *data)
{
	genlist *sl_sp, *sl_ep;
	register long list_cnt = obj->track_items, rg_val, rg_mean, oo;
	static int x = 5;

	if (sl_s == sl_e)
		; /* just replace */
	sl_e = list_cnt - sl_e;
	if (sl_e > list_cnt)
		; /* not good */

	sl_sp = obj->list;
	sl_ep = obj->last;
	rg_val = sl_e - sl_s;
	rg_mean = (unsigned long)rg_val >> 1;

	for (;;)
	{
		if (sl_s--)
			sl_sp = sl_sp->f;
		if (sl_e--)
			sl_ep = sl_ep->b;
		if (sl_s == 0 && sl_e == 0)
			break;
	}
	while (rg_hmean--)
	{
		sl_sp->data = obj->pointer_mem ? *(unsigned char **)((char *)data++) : (unsigned char *)data++;
	}
}
void ccl_delete(Object_List *obj)
{
	struct genlist *n;

	if (obj->list == NULL)
		return;

	while (obj->list != NULL)
	{
		n = obj->list;
		obj->list = obj->list->f;
		free(n);
	}
	obj->last = NULL;
	obj->list = NULL;
}

#endif
