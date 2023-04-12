#include <stdio.h>
#include "arraylist.h"

int main(int argc, char *argv[])
{
    printf("Starting data structures ...\n");

    list_t list = list_interface->create(&arraylist_implementation);
    (void) list;

    return 0;
}
