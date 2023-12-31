﻿#ifndef CCL_LIST_H
#define CCL_LIST_H
#if defined(__GNUC__) || defined(__CLANG__)
/* #define __BUILTIN_LIST_SUPPORT__ */
    #if defined(GCC_TYPECLASS_H)
        #include <typeclass.h>
    #endif
#endif
#ifdef LIST_THREAD_SAFE
    #if USE_PTHREAD_LOCK
        #define LOCK pthread_lock()
        #define UNLOCK pthread_unlock()
    #else
        #define LOCK thread_lock()
        #define UNLOCK thread_unlock()
    #endif
#endif
#include "clistproto.h"

#define __UNUSED__ __attribute__((unused))

#ifdef __BUILTIN_LIST_SUPPORT__
#include <stdarg.h>
#undef list
#define __builtin_assert_ptype(T)\
	(__builtin_classify_type((T)0) == __builtin_classify_type((void *)0))
#define _BUFFER(type, n)\
	(__builtin_assert_ptype(type) ? (void *)((type *[(n)]){0}) : (void *)((type [(n)]){0}))
#define list(obj, ...)							\
	do {\
		if (! __builtin_types_compatible_p(__typeof__(obj), Object_List)) abort(); \
		if (! CHOOSE_ARG(1 __VA_OPT__(,) - 1)) { abort(); __builtin_unreachable(); } \
		typedef __typeof__ ((void)0, CHOOSE_ARG(__VA_OPT__(__VA_ARGS__,) (void)0)) obj ## _clst_lltype; \
		listp(&obj, #obj, (cc_marker){__builtin_assert_ptype(obj ## _clst_lltype), \
					0, 0, sizeof (obj ## _clst_lltype), NUMAR___G(__VA_ARGS__)}, \
			(void *)(_BUFFER(obj ## _clst_lltype, NUMAR___G(__VA_ARGS__))) __VA_OPT__(, __VA_ARGS__)); \
	} while (0)

void init(Object_List *obj, char *obj_name, cc_marker marker, void *buffer, ...)
{
	va_list listArguments;

	if (obj == NULL || buffer == NULL)
		return;
	object->loc_obj_name = obj_name;

	object->list = object->last = NULL;
	object->track_items = 0;
	va_start(bufffer, listArguments);
}
#else
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
#endif
#define abs_num(a) ((a) > 0 ? (a) : -(a))
void ccl_range(Object_List *__restrict__ obj, long start, long stop, long step)
{
	struct genlist *n = NULL, **ptr_last = NULL;
	int abs_st = 0, oo = 0, tmp_st = 0;

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


#define __CCL_TYPEOF__(d) (__typeof__(((void)0, d)))
#define __CCL_SIZEOF__(d) (__sizeof__(((void)0, d)))
#define LIST_SIZE_MAX 256

#define cc_slice(obj, s, e, d)											\
	slice(obj, s, e, __CCL_SIZEOF__(d), (__CCL_TYPEOF__(d)[LIST_SIZE_MAX]){data});

//!(x < LIST_SIZE_MAX) ? ((typeof (data)[x])(data)) : malloc(sizeof (data) * size);
/**
   < -len = 0
 < 0 = len + st
>= len = len(add)
 */
/* start.x
 * rem
we are starting x if rem is 0 - x to end

if inputs given is less than x, and its not single replace only some
if it is single slice(X, 5) replace (start to stop with 5)

x < -len

(5, 0, 6
 */
void slice(Object_List *obj, int sl_s, int sl_e, size_t siz, void *data)
{
	genlist *sl_sp, *sl_ep;
	register long list_cnt = obj->track_items, rg_val, rg_mean, oo;
	static long x[3] = {123, 234, 456};

	sl_s = (sl_s < -list_cnt) ? 0
		: (sl_s < 0) ? sl_s + list_cnt
		: (sl_s >= list_cnt && sl_e) ? list_cnt /* append to last */ : /* no change */ sl_s;

	if (sl_s != list_cnt)
		sl_e = (sl_e < 0) ? list_cnt + sl_e
			: (sl_e > list_cnt) ? list_cnt : /* no change */ sl_e;
	else
		sl_e = list_cnt + siz;

	if (sl_e < -list_cnt)
		goto do_nothing;

	sl_sp = obj->list;
	sl_ep = obj->last;

	while  (sl_s-- && sl_sp)
		sl_sp = sl_sp->f;

	siz = 3;
	while (sl_e-- && siz--)
	{
		sl_sp->data = (void *)x;
		sl_sp = sl_sp->f;
	}
do_nothing:
	/* lets do nothing here */
	(void)0;
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

/*

		if (obj->pointer_mem)
		{
			sl_sp->data = *(unsigned char **)((char *)data++);
			sl_ep->data = *(unsigned char **)((char *)data++);
			continue;
		}
		sl_sp->data = (char *)data++;
		sl_ep->data = (char *)data++;
*/
