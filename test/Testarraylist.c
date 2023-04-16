//
// Created by Christian Vasquez on 13/4/2023.
//
#include <stdio.h>
#include <stdbool.h>

#include "../src/list.h"
#include "../src/arraylist.h"
#include "../unity/src/unity.h"
#include "../src/data_structures_test.h"

static
list_t list;

static
void dispose_fn(const void *kv) {
    free((void *) kv);
}

static
bool equals_fn(const void *elt1, const void *elt2)
{
    return *((int *)elt1) == *((int *)elt2);
}

static
int compare_fn(const void *elt1, const void *elt2)
{
    return *((int *)elt2) - *((int *)elt1);
}

void setUp(void)
{
    printf("\nSet Up called.\n");
    list = list_interface->create(&arraylist_implementation,
                                         equals_fn,
                                         compare_fn,
                                         dispose_fn,
                                         true);
}

void tearDown(void)
{
    printf("Tear Down called.\n");
    list_interface->free_list(list);
}

void test_TrialTest(void)
{
    printf("test_TrialTest called.\n");
    TEST_ASSERT(true);
}

void test_ArrayListCreateShouldNotReturnNull(void)
{
    printf("test_ArrayListCreateShouldNotReturnNull called.\n");
    TEST_ASSERT_NOT_NULL(list);
}

void test_ArrayListNewlyCreateShouldHaveSizeZero(void)
{
    printf("test_ArrayListNewlyCreateShouldHaveSizeZero called.\n");
    TEST_ASSERT_EQUAL(0, list_interface->size(list));
}

int main(int argc, char *argv[])
{
    UNITY_BEGIN();
    RUN_TEST(test_TrialTest);
    RUN_TEST(test_ArrayListCreateShouldNotReturnNull);
    RUN_TEST(test_ArrayListNewlyCreateShouldHaveSizeZero);
    run();
    return UNITY_END();
}
