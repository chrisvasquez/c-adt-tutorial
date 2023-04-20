#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#ifndef uintptr_t
#include <stdint.h>
#endif

#include "arraylist.h"

/* struct list_node_impl does not need to be implemented here.
 * The pointers are actually just indices + 1. The list_node_t is just
 * the 1-indexed position of the node in the list.
 * This would be more relevant for other concrete data types like linked lists
 * where each node contains more information that just the value of the element.
 * The node contains information regarding, for example, the pointer to the
 * next node and the pointer to the previous node.
 */
#define INDEX_TO_NODE(index) (list_node_t)(uintptr_t)(size_t)((index) + 1)
#define NODE_TO_INDEX(node) ((uintptr_t)(node)-1)

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

static bool
pointer_equals(const void *elt1, const void *elt2)
{
    return elt1 == elt2;
}

static list_t
create(list_implementation_t implementation,
                     list_element_equals_fn equals_fn,
                     list_element_compare_fn compare_fn,
                     list_element_dispose_fn dispose_fn,
                     bool allow_duplicates)
{
    struct list_impl *list =
            (struct list_impl *) calloc(sizeof(struct list_impl), 1);
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

static size_t
size(list_t list)
{
    return list->count;
}

static const void *
get_at(list_t list, size_t index)
{
    /**
     * 1.08j:issue
     * Should a non existent item / index return NULL?
     * Should there be an error indicator for when the call to a function fails
     * without crashing the program?
     * I say yes.
     */
    if (index >= list->count)
        /* option 1 : crash the program */
        /* Invalid state / parameter */
        //abort();

        /* option 2 : do not crash the program */
        // could return NULL or a boolean for success or failure
        // while having a parameter passed getting the value of the results
        return NULL;

    return (const void *)list->elements[index];
}

static const void *
get_first(list_t list)
{
    if (list->count == 0)
        /* Invalid call, no element present if count = 0 */
        abort();
    return (const void *)list->elements[0];
}

static const void *
get_last(list_t list)
{
    size_t count = list->count;
    if (count == 0)
        /* Invalid call, no element present if count = 0 */
        abort();
    return (const void *)list->elements[count - 1];
}

static const void *
add_last(list_t list, void *elt) {
    size_t count = list->count;

    if (count == list->capacity)
        if (grow(list) < 0)
            return NULL;
    list->elements[count] = elt;
    list->count = count + 1;
    return list->elements[count];
}

static const void *
add_first(list_t list, void *elt)
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

static const void *
add_at(list_t list, void *elt, size_t index)
{
    size_t count = list->count;
    const void **elements;
    size_t i;

    if (index >= count)
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

static const void *
node_value(list_t list, list_node_t node)
{
    uintptr_t index = NODE_TO_INDEX(node);
    if (index >= list->count)
        /* Invalid argument.  */
        abort();
    return list->elements[index];
}

/**
 *
 * @param list
 * @param node
 * @param elt
 * @return
 *
 * Concerns regarding the old value of at the index location.
 * Should it be freed?
 * What if there is something pointing to it still?
 */
static int
set_node_value(list_t list, list_node_t node, const void *elt)
{
    size_t index = NODE_TO_INDEX(node);
    if (index >= list->count)
        abort();
    const void *e = list->elements[index];
    list->elements[index] = elt;
    free((void *)e);
    return 0;
}


static list_node_t
first_node(list_t list)
{
    if (list->count > 0) {
        return INDEX_TO_NODE(0);
    }
    else
        return NULL;
}

static list_node_t
last_node(list_t list)
{
    if (list->count > 0) {
        return INDEX_TO_NODE(list->count - 1);
    }
    else
        return NULL;
}

static list_node_t
previous_node(list_t list, list_node_t node)
{
    size_t index = NODE_TO_INDEX(node);
    if (list->count > 0) {
        return INDEX_TO_NODE(index - 1);
    }
    else
        return NULL;
}

static list_node_t
next_node(list_t list, list_node_t node)
{

    size_t index = NODE_TO_INDEX(node);
    if (index < list->count - 2) {
        return INDEX_TO_NODE(index + 1);
    }
    else
        return NULL;
}

static list_node_t
nx_get_at(list_t list, size_t index)
{
    size_t count = list->count;
    if (index >= count)
        return NULL;
    return INDEX_TO_NODE(index);
}

static bool
contains(list_t list, void *elt)
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

static void
free_list(list_t list)
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

static
bool remove_at(list_t list, size_t index)
{
    size_t count = list->count;
    const void **elements = list->elements;
    size_t i;

    if (index >= count)
        return false;
    if (list->base.dispose_fn != NULL)
        list->base.dispose_fn(elements[index]);
    for (i = index + 1; i < count; i++) {
        elements[i - 1] = elements[i];
    }
    list->count = count - 1;
    return true;
}


static
bool remove_first(list_t list)
{
    return remove_at(list, 0);
}

static
bool remove_last(list_t list)
{
    size_t count = list->count;
    if (count == 0)
        return false;
    return remove_at(list, count - 1);
}

const struct list_implementation arraylist_implementation = {create,
                                                             size,

                                                             get_at,
                                                             get_first,
                                                             get_last,

                                                             add_at,
                                                             add_first,
                                                             add_last,

                                                             remove_at,
                                                             remove_first,
                                                             remove_last,

                                                             node_value,
                                                             set_node_value,

                                                             first_node,
                                                             last_node,
                                                             previous_node,
                                                             next_node,
                                                             nx_get_at,

                                                             contains,
                                                             free_list};
