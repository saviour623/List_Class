#include "clistproto.h"
/**
   typedef struct Object_List {
   struct genlist *list;
   struct genlist *last;
   struct Object_List *objself;
   char * const loc_obj_name;
   uintmax_t track_items;
   uintptr_t cll_local_address;
   void (*add)(struct Object_List *, void *); //will also assign type
   void (*config_addData)(Object_List *, bool, size_t, size_t, bool, void *);
   void (*remove)(struct Object_List *,  ...);
   } cclist_obj_t;
*/
/*
  void *data;
  int range_tmp;
  struct genlist *forward_node;
  struct genlist * backward_node;
  };

*/
#define ERRMEM 0
#define ERRNULL 1
int error_routine(unsigned long err)
{
	(void)err;
	exit(EXIT_FAILURE);
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

void init(Object_List *object, char * const obj_name, cc_marker marker, void *data){
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

__attribute__((unused)) static void ccl_add_init(Object_List *obj, void *data, cc_marker info)
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
