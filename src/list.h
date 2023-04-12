#ifndef TEAM_VASQUEZ_LIST_H
#define TEAM_VASQUEZ_LIST_H

#include <stdlib.h>
#include <stdbool.h>

/* Type of function used to compare two elements.
   NULL denotes pointer comparison.  */
typedef bool (*list_element_equals_fn)(const void *elt1, const void *elt2);

/* Type of function used to dispose an element once it's removed from a list.
   NULL denotes a no-op.  */
typedef void (*list_element_dispose_fn)(const void *elt);

/* Type of function used to 2 elements:
   -1 : elt1  < elt2
    0 : elt1 == elt2
    1 : elt1  > elt2
    0 : is compatible with equals
   NULL denotes a no-op.  */
typedef int (*list_element_compare_fn)(const void *elt1, const void *elt2);

struct list_impl;
/******************************************************************************
 * Type representing an entire list.
 *
 * The `list_t` will be used here by the struct `list_impl` will have
 * different private implementations in the implementaton or .c files of each
 * concrete data type.
 *****************************************************************************/
typedef struct list_impl *list_t;

struct list_implementation;
/******************************************************************************
 * Type representing an implementation of the abstract data type in concrete
 * data types..
 *
 * The `list_implementation` will declared here and the `list_implementation_t`
 * will be the type of the concrete implementation of the abstract data type.
 *****************************************************************************/
typedef const struct list_implementation *list_implementation_t;

/******************************************************************************
 * Type representing the base implementation of the concrete data type.
 *
 * This is the basic elements needed to implement the abstract data type.
 *****************************************************************************/
struct list_impl_base
{
    /* Will hold the struct that implements the concrete data type implementation
       of the functions needed by the `list_interface.` */
    const struct list_implementation *fn_table;
    list_element_equals_fn equals_fn;
    list_element_compare_fn compare_fn;
    list_element_dispose_fn dispose_fn;
    bool allow_duplicates;
};

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
 *
 * The `create` function will inject in the list the implementation which is
 * the interface to the concrete implementation type of the data type. Thus,
 * all the remaining functions will have access to the `implementation`
 * parameter through the `list` parameter.
 *****************************************************************************/
struct list_intf
{
    list_t (*create)(list_implementation_t implementation,
                     list_element_equals_fn equals_fn,
                     list_element_compare_fn compare_fn,
                     list_element_dispose_fn dispose_fn,
                     bool allow_duplicates);
    size_t (*size)(list_t list);
    const void *(*get_at)(list_t list, size_t index);
    const void *(*get_first)(list_t list);
    const void *(*get_last)(list_t list);
    const void *(*add_last)(list_t list, void *elt);
    const void *(*add_first)(list_t list, void *elt);
    const void *(*add_at)(list_t list, void *elt, size_t index);
    bool (*contains)(list_t list, void *elt);
};

extern const struct list_intf *list_interface;

struct list_implementation
{
    list_t (*create)(list_implementation_t implementation,
                     list_element_equals_fn equals_fn,
                     list_element_compare_fn compare_fn,
                     list_element_dispose_fn dispose_fn,
                     bool allow_duplicates);
    size_t (*size)(list_t list);
    const void *(*get_at)(list_t list, size_t index);
    const void *(*get_first)(list_t list);
    const void *(*get_last)(list_t list);
    const void *(*add_last)(list_t list, void *elt);
    const void *(*add_first)(list_t list, void *elt);
    const void *(*add_at)(list_t list, void *elt, size_t index);
    bool (*contains)(list_t list, void *elt);
};

#endif // TEAM_VASQUEZ_LIST_H
