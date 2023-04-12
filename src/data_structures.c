#include <stdio.h>
#include <stdbool.h>

#include "arraylist.h"

void dispose_fn(const void *kv) {
    free((void *) kv);
}

bool equals_fn(const void *elt1, const void *elt2)
{
    return *((int *)elt1) == *((int *)elt2);
}

int compare_fn(const void *elt1, const void *elt2)
{
    return *((int *)elt2) - *((int *)elt1);
}

int main(int argc, char *argv[])
{
    printf("Starting data structures ...\n");

    list_t list = list_interface->create(&arraylist_implementation,
                                         equals_fn,
                                         compare_fn,
                                         dispose_fn,
                                         true);


    size_t size;

    // Query the size of the list
    size = list_interface->size(list);
    printf("The size of the list is currently: %zu.\n", size);

    int N = 5;

    for (int i = 0; i < N; i++){
        int *k = (int *)malloc(sizeof(int));
        *k = i;
        list_interface->add_last(list, k);
    }
    printf("The size of the list is currently: %zu.\n", list_interface->size(list));

    size = list_interface->size(list);
    for (int i = 0; i < size; i++)
    {
        int k = *((int *)list_interface->get_at(list, i));
        printf("%d : %d\n", i, k);
    }
    printf("\n");

    for (int i = N; i < 2 * N; i++){
        int *k = (int *)malloc(sizeof(int));
        *k = i;
        list_interface->add_first(list, k);
    }
    printf("The size of the list is currently: %zu.\n", list_interface->size(list));

    size = list_interface->size(list);
    for (int i = 0; i < size; i++)
    {
        int k = *((int *)list_interface->get_at(list, i));
        printf("%d : %d\n", i, k);
    }
    printf("\n");

    for (int i = 0; i < 2 * N; i += 2){
        int *k = (int *)malloc(sizeof(int));
        *k = i;
        list_interface->add_at(list, k, i);
    }
    printf("The size of the list is currently: %zu.\n", list_interface->size(list));

    size = list_interface->size(list);
    for (int i = 0; i < size; i++)
    {
        int k = *((int *)list_interface->get_at(list, i));
        printf("%d : %d\n", i, k);
    }
    printf("\n");

    int k = *((int *)list_interface->get_first(list));
    printf("Element at the start: %d\n", k);

    k = *((int *)list_interface->get_last(list));
    printf("Element at the end: %d\n", k);


    int *e1 = (int *)list_interface->get_last(list);
    *e1 = 5;

    printf("Element at the last position is :%d\n", *e1);

    int *e2 = (int *)list_interface->get_last(list);
    printf("Element at the last position is :%d\n", *e2);

    int e3 = 4;

    printf("Contains   %d: %d.\n", e3, (int) list_interface->contains(list, &e3));

    int e4 = 400;

    printf("Contains %d: %d.\n", e4, (int) list_interface->contains(list, &e4));

    list_node_t first_node = list_interface->first_node(list);

    int *first_node_value = (int *)list_interface->node_value(list, first_node);

    printf("Original value : %d\n", *first_node_value);

    int *new_value = (int *)malloc(sizeof(int *));
    *new_value = 100;
    list_interface->set_node_value(list, first_node, new_value);
    int new_value_set = *((int *)list_interface->get_at(list, 0));
    printf("New value : %d\n", new_value_set);

    list_interface->free_list(list);

    return 0;
}

