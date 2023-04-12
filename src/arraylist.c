#include <stdlib.h>
#include <stdbool.h>

#include "arraylist.h"

/* Concrete tv_list_impl type, valid for this file only.  */
struct list_impl
{
    struct list_impl_base base;
    /* An array of ALLOCATED elements, of which the first COUNT are used.
       0 <= COUNT <= ALLOCATED.  */
    const void **elements;
    size_t count;
    size_t capacity;
};

static list_t create(list_implementation_t implementation,
                     list_element_equals_fn equals_fn,
                     list_element_compare_fn compare_fn,
                     list_element_dispose_fn dispose_fn,
                     bool allow_duplicates)
{
    struct list_impl *list =
            (struct list_impl *) malloc(sizeof(struct list_impl));
    if (list == NULL)
        return NULL;

    list->base.fn_table = implementation;
    list->base.equals_fn = equals_fn;
    list->base.compare_fn = compare_fn;
    list->base.dispose_fn = dispose_fn;
    list->base.allow_duplicates = allow_duplicates;
    list->count = 0;
    list->capacity = 0;

    return list;
}

static size_t size(list_t list)
{
    return list->count;
}

static void *get_at(list_t list, size_t index)
{
    return NULL;
}

static void *get_first(list_t list)
{
    return NULL;
}

static void *get_last(list_t list)
{
    return NULL;
}

static void *add_last(list_t list, void *elt)
{
    return NULL;
}

static void *add_first(list_t list, void *elt)
{
    return NULL;
}

static void *add_at(list_t list, void *elt, size_t index)
{
    return NULL;
}

static bool contains(list_t list, void *elt)
{
    return true;
}

const struct list_implementation arraylist_implementation = {create,
                                                             size,
                                                             get_at,
                                                             get_first,
                                                             get_last,
                                                             add_last,
                                                             add_first,
                                                             add_at,
                                                             contains};
