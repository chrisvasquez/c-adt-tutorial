#include <stdio.h>
#include <stdbool.h>

#include "arraylist.h"

int main(int argc, char *argv[])
{
    printf("Starting data structures ...\n");

    list_t list = list_interface->create(&arraylist_implementation,
                                         NULL,
                                         NULL,
                                         NULL,
                                         true);

    // Query the size of the list
    size_t size = list_interface->size(list);
    printf("The size of the list is currently: %zu.\n", size);

    (void) list;

    return 0;
}
