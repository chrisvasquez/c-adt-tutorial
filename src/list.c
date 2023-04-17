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

static const void *add_last(list_t list, void *elt)
{
    return ((const struct list_impl_base *)list)->fn_table->add_last(list, elt);
}

static const void *add_first(list_t list, void *elt)
{
    return ((const struct list_impl_base *)list)->fn_table->add_first(list, elt);
}

static const void *add_at(list_t list, void *elt, size_t index)
{
    return ((const struct list_impl_base *)list)->fn_table->add_at(list, elt, index);
}

static const void *node_value(list_t list, list_node_t node)
{
    return ((const struct list_impl_base *)list)->fn_table->node_value(list, node);
}

static int set_node_value(list_t list, list_node_t node, const void *elt)
{
    return ((const struct list_impl_base *)list)->fn_table->set_node_value(list, node, elt);
}

static list_node_t first_node(list_t list)
{
    return ((const struct list_impl_base *)list)->fn_table->first_node(list);
}


static list_node_t last_node(list_t list)
{
    return ((const struct list_impl_base *)list)->fn_table->last_node(list);
}

static bool remove_at(list_t list, size_t index)
{
    return ((const struct list_impl_base *)list)->fn_table->remove_at(list, index);
}


static bool remove_first(list_t list)
{
    return ((const struct list_impl_base *)list)->fn_table->remove_first(list);
}


static bool remove_last(list_t list)
{
    return ((const struct list_impl_base *)list)->fn_table->remove_last(list);
}

static bool contains(list_t list, void *elt)
{
    return ((const struct list_impl_base *)list)->fn_table->contains(list, elt);
}

void free_list(list_t list)
{
    ((const struct list_impl_base *)list)->fn_table->free_list(list);
}

static const struct list_intf list_interface_implementation = {create,
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

                                                               contains,
                                                               free_list};

const struct list_intf *list_interface = &list_interface_implementation;
