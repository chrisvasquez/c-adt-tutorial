#include <stdlib.h>
#include <stdbool.h>

#include "arraylist.h"

static list_t create(list_implementation_t implementation)
{
    return NULL;
}

static size_t size(list_t list)
{
    return 0;
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
