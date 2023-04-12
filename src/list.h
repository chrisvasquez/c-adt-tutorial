#ifndef TEAM_VASQUEZ_LIST_H
#define TEAM_VASQUEZ_LIST_H

#include <stdlib.h>

struct list_impl;
/******************************************************************************
 * Type representing an entire list.
 *
 * The `list_t` will be used here by the struct `list_impl` will have
 * different private implementations in the implementaton or .c files of each
 * concrete data type.
 *****************************************************************************/
typedef struct list_impl *list_t;

/******************************************************************************
 * Most of the functions here returns `void *` which is just an assumption that
 * there will be a returned value. The most appropriate value will be decided
 * later. It could be a pointer to a list node type that could be determined
 * later.
 *
 * Further, the function parameters' type are either a determined type or
 * void * for type that will be determined later.
 *
 * The implementation parameter if the interface to the specific implemenmtation
 * of the abstract data type. List is the abstract data type and an example of
 * the implementation in a concrete data type is a dynamic array. The parameter
 * `implementation` would be used to gain access to the concrete data type
 * functions specific to that type.
 *****************************************************************************/
typedef struct list_intf
{
    list_t (*create)(void *implementation);
    size_t (*size)(void *list);
    void *(*get_at)(void *list);
    void *(*get_first)(void *list);
    void *(*get_last)(void *list);
    void *(*add_last)(void *list, void *elt);
    void *(*add_first)(void *list, void *elt);
    void *(*add_add)(void *list, void *elt, size_t index);
    bool (*contains)(void *list, void *elt);
} list_intf;

#endif