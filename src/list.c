#include <stdlib.h>
#include <stdbool.h>

#include "list.h"

static list_t create(list_implementation_t implementation,
                     list_element_equals_fn equals_fn,
                     list_element_compare_fn compare_fn,
                     list_element_dispose_fn dispose_fn,
                     bool allow_duplicates)
{
    return implementation->create(implementation,
                                  equals_fn,
                                  compare_fn,
                                  dispose_fn,
                                  allow_duplicates);
}

static size_t size(list_t list)
{
    return ((const struct list_impl_base *)list)->fn_table->size(list);
}

static const void *get_at(list_t list, size_t index)
{
    return ((const struct list_impl_base *)list)->fn_table->get_at(list, index);
}

static const void *get_first(list_t list)
{
    return ((const struct list_impl_base *)list)->fn_table->get_first(list);
}

static const void *get_last(list_t list)
{
    return ((const struct list_impl_base *)list)->fn_table->get_last(list);
}

static void *add_last(list_t list, void *elt)
{
    return ((const struct list_impl_base *)list)->fn_table->add_last(list, elt);
}

static void *add_first(list_t list, void *elt)
{
    return ((const struct list_impl_base *)list)->fn_table->add_first(list, elt);
}

static void *add_at(list_t list, void *elt, size_t index)
{
    return ((const struct list_impl_base *)list)->fn_table->add_at(list, elt, index);
}

static bool contains(list_t list, void *elt)
{
    return true;
}

static const struct list_intf list_interface_implementation = {create,
                                                               size,
                                                               get_at,
                                                               get_first,
                                                               get_last,
                                                               add_last,
                                                               add_first,
                                                               add_at,
                                                               contains};

const struct list_intf *list_interface = &list_interface_implementation;
