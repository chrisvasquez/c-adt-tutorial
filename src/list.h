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

struct list_node_impl;
/******************************************************************************
 * Type representing a node entry.
 *
 * The `list_node_t` will be used here but the implementation details in the
 * form of `list_node_impl` will be declared in each conrete implementation of
 * the list data type.
 *****************************************************************************/
typedef struct list_node_impl *list_node_t;

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

    const void *(*add_at)(list_t list, void *elt, size_t index);
    const void *(*add_first)(list_t list, void *elt);
    const void *(*add_last)(list_t list, void *elt);

    bool (*remove_at)(list_t list, size_t index);
    bool (*remove_first)(list_t list);
    bool (*remove_last)(list_t list);

    const void *(*node_value)(list_t list, list_node_t noe);
    int (*set_node_value)(list_t list, list_node_t node, const void *elt);

    list_node_t (*first_node)(list_t list);
//    list_node_t (*last_node)(list_t list);
//    list_node_t (*previous_node)(list_t list, list_node_t node);
//    list_node_t (*next_node)(list_t list, list_node_t node);
//    list_node_t (*nx_get_at)(list_t list, size_t index);
//    list_node_t (*nx_set_at)(list_t list, const void *elt, size_t index);
//    list_node_t (*nx_add_at)(list_t list, const void *elt, size_t index);
//    list_node_t (*nx_add_first)(list_t list, const void *elt);
//    list_node_t (*nx_add_last)(list_t list, const void *elt);
//    list_node_t (*nx_add_before)(list_t list, const void *elt, list_node_t node);
//    list_node_t (*nx_add_after)(list_t list, const void *elt, list_node_t node);

// Searching
//    list_node_t (*search_from_to)(list_t list, const void *elt, size_t
//            start_index, size_t end_index);
//    size_t (*index_of_from_to)(list_t list, const void *elt,
//            size_t start_index, size_t end_index);

// Removal
//    bool (*remove_node)(list_t list, list_node_t node);
//    bool (*remove_first)(list_t list, size_t index);
//    bool (*remove_last )(list_t list, size_t index);
//    bool (*remove_elt)(list_t list, const void *elt);

    bool (*contains)(list_t list, void *elt);

// /* tv_list_iterator_t functions.  */
//    list_iterator_t (*iterator)(list_t list);
//
//    list_iterator_t (*iterator_from_to)(list_t list,
//                                        size_t start_index,
//                                        size_t end_index);
//
//    bool (*iterator_next)(list_iterator_t *iterator,
//                          const void **eltp, list_node_t *nodep);
//
//    void (*iterator_free)(list_iterator_t *iterator);
//
//    // /* Sorted tv_list_t functions.  */
//    list_node_t (*sorted_list_search)(list_t list,
//                                      list_element_compare_fn compare_fn,
//                                      const void *elt);
//
//    list_node_t (*sorted_list_search_from_to)(list_t list,
//                                              list_element_compare_fn compare_fn,
//                                              const void *elt,
//                                              size_t start_index,
//                                              size_t end_index);
//
//    size_t (*sorted_list_index_of)(list_t list,
//                                   list_element_compare_fn compare_fn,
//                                   const void *elt);
//
//    size_t (*sorted_list_index_of_from_to)(list_t list,
//                                          list_element_compare_fn compare_fn,
//                                          const void *elt,
//                                          size_t start_index, size_t end_index);
//
//    list_node_t (*sorted_list_nx_add)(list_t list,
//                                      list_element_compare_fn compare_fn,
//                                      const void *elt);
//
//    bool (*sorted_list_remove)(list_t list,
//                               list_element_compare_fn compare_fn,
//                               const void *elt);

//    void (*clear_list)(list_t list);
    void (*free_list)(list_t list);
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

    const void *(*add_at)(list_t list, void *elt, size_t index);
    const void *(*add_first)(list_t list, void *elt);
    const void *(*add_last)(list_t list, void *elt);

    bool (*remove_at)(list_t list, size_t index);
    bool (*remove_first)(list_t list);
    bool (*remove_last)(list_t list);

    const void *(*node_value)(list_t list, list_node_t node);
    int (*set_node_value)(list_t list, list_node_t node, const void *elt);

    list_node_t (*first_node)(list_t list);

    bool (*contains)(list_t list, void *elt);
    void (*free_list)(list_t list);
};

#endif // TEAM_VASQUEZ_LIST_H
