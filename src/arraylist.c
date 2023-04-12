#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

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

/* Ensure that list->allocated > list->count.
   Return 0 upon success, -1 upon out-of-memory.  */
static int
grow(list_t list)
{
    size_t new_allocated;
    size_t memory_size;
    const void **memory;

    new_allocated = list->capacity * 2;
    new_allocated += 1;
    memory_size = new_allocated * sizeof(const void *);
    if (memory_size == SIZE_MAX)
        /* Overflow, would lead to out of memory.  */
        return -1;
    memory = (const void **)realloc(list->elements, memory_size);
    if (memory == NULL)
        /* Out of memory.  */
        return -1;
    list->elements = memory;
    list->capacity = new_allocated;
    return 0;
}

static bool pointer_equals(const void *elt1, const void *elt2)
{
    return elt1 == elt2;
}

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

static const void *get_at(list_t list, size_t index)
{
    if (index > list->count)
        /* Invalid state / parameter */
        abort();

    return (const void *)list->elements[index];
}

static const void *get_first(list_t list)
{
    if (list->count == 0)
        /* Invalid call, no element present if count = 0 */
        abort();
    return (const void *)list->elements[0];
}

static const void *get_last(list_t list)
{
    size_t count = list->count;
    if (count == 0)
        /* Invalid call, no element present if count = 0 */
        abort();
    return (const void *)list->elements[count - 1];
}

static const void *add_last(list_t list, void *elt) {
    size_t count = list->count;

    if (count == list->capacity)
        if (grow(list) < 0)
            return NULL;
    list->elements[count] = elt;
    list->count = count + 1;
    return list->elements[count];
}

static const void *add_first(list_t list, void *elt)
{
    size_t count = list->count;
    const void **elements;
    size_t i;

    if (count == list->capacity)
        if (grow(list) < 0)
            return NULL;
    elements = list->elements;
    for (i = count; i > 0; i--)
        elements[i] = elements[i - 1];
    elements[0] = elt;
    list->count = count + 1;
    return list->elements[0];
}

static const void *add_at(list_t list, void *elt, size_t index)
{
    size_t count = list->count;
    const void **elements;
    size_t i;

    if (!(index <= count))
        /* Invalid argument.  */
        abort();
    if (count == list->capacity)
        if (grow(list) < 0)
            return NULL;
    elements = list->elements;
    for (i = count; i > index; i--)
        elements[i] = elements[i - 1];
    elements[index] = elt;
    list->count = count + 1;
    return list->elements[index];
}

static bool contains(list_t list, void *elt)
{
    list_element_equals_fn equals_fn =
            list->base.equals_fn != NULL
            ? list->base.equals_fn
            : pointer_equals;

    for (size_t i = 0; i < list->count; i++)
    {
        if (equals_fn(elt, list->elements[i]))
            return true;
    }
    return false;
}

static void free_list(list_t list)
{
    if (list->elements != NULL)
    {
        if (list->base.dispose_fn != NULL)
        {
            size_t count = list->count;

            if (count > 0)
            {
                list_element_dispose_fn dispose = list->base.dispose_fn;
                const void **elements = list->elements;

                do
                    dispose(*elements++);
                while (--count > 0);
            }
        }
        free(list->elements);
    }
    free(list);
}

const struct list_implementation arraylist_implementation = {create,
                                                             size,
                                                             get_at,
                                                             get_first,
                                                             get_last,
                                                             add_last,
                                                             add_first,
                                                             add_at,
                                                             contains,
                                                             free_list};
