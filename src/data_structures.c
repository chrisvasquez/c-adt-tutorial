#include <stdio.h>
#include <stdbool.h>

#include "arraylist.h"

void dispose_fn(const void *kv) {
    free((void *) kv);
}

int main(int argc, char *argv[])
{
    printf("Starting data structures ...\n");

    list_t list = list_interface->create(&arraylist_implementation,
                                         NULL,
                                         NULL,
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

    list_interface->free_list(list);

    return 0;
}
