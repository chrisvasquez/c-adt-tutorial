#include <stdlib.h>
#include <stdbool.h>

#include "list.h"

static list_t create(list_implementation_t implementation)
{
    return implementation->create(implementation);
}

static size_t size(list_t list)
{
    return ((const struct list_impl_base *)list)->fntable->size(list);
}

static void *get_at(list_t list, size_t index)
{
    return ((const struct list_impl_base *)list)->fntable->get_at(list, index);
}

static void *get_first(list_t list)
{
    return ((const struct list_impl_base *)list)->fntable->get_first(list);
}

static void *get_last(list_t list)
{
    return ((const struct list_impl_base *)list)->fntable->get_last(list);
}

static void *add_last(list_t list, void *elt)
{
    return ((const struct list_impl_base *)list)->fntable->add_last(list, elt);
}

static void *add_first(list_t list, void *elt)
{
    return ((const struct list_impl_base *)list)->fntable->add_first(list, elt);
}

static void *add_at(list_t list, void *elt, size_t index)
{
    return ((const struct list_impl_base *)list)->fntable->add_at(list, elt, index);
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
