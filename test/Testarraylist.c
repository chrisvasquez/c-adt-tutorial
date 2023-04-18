//
// Created by Christian Vasquez on 13/4/2023.
//
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>

#include "../src/list.h"
#include "../src/arraylist.h"
#include "../unity/src/unity.h"
#include "data_structures_test.h"

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
    list = list_interface->create(&arraylist_implementation,
                                         equals_fn,
                                         compare_fn,
                                         dispose_fn,
                                         true);
}

void tearDown(void)
{
    list_interface->free_list(list);
}

void test_TrialTest(void)
{
    TEST_ASSERT(true);
}

void test_ArrayListCreateShouldNotReturnNull(void)
{
    TEST_ASSERT_NOT_NULL(list);
}

void test_ArrayListNewlyCreateShouldHaveSizeZero(void)
{
    TEST_ASSERT_EQUAL(0, list_interface->size(list));
}

void test_ArrayListGetAtOnEmptyList(void)
{
    TEST_ASSERT_NULL(list_interface->get_at(list, 2));
}

void test_ArrayListAddFirst(void)
{
    int n = 1000;
    int *k = (int *)malloc(sizeof (int));
    *k = 3;
    const void *result = list_interface->add_first(list, k);
    TEST_ASSERT_NOT_NULL(result);
    const int *result_int = (const int *)result;
    TEST_ASSERT_EQUAL(3, *result_int);
    TEST_ASSERT_EQUAL(k, result);
    for (int i = 0; i < n; i++)
    {
        int *number = (int *)malloc(sizeof(int));
        *number = i;
        list_interface->add_first(list, number);
    }
    TEST_ASSERT_EQUAL(n + 1, list_interface->size(list));
}

void test_ArrayListAddLast(void)
{
    int n = 1000;
    int *k = (int *)malloc(sizeof (int));
    *k = 3;
    const void *result = list_interface->add_last(list, k);
    TEST_ASSERT_NOT_NULL(result);
    const int *result_int = (const int *)result;
    TEST_ASSERT_EQUAL(3, *result_int);
    TEST_ASSERT_EQUAL(k, result);
    for (int i = 0; i < n; i++)
    {
        int *number = (int *)malloc(sizeof(int));
        *number = i;
        list_interface->add_last(list, number);
    }
    TEST_ASSERT_EQUAL(n + 1, list_interface->size(list));
}


void test_ArrayListAddAt(void)
{
    int n = 1000;
    for (int i = 0; i < n; i++) {
        int *number = (int *)malloc(sizeof(int));
        *number = i;
        list_interface->add_last(list, number);
    }
    TEST_ASSERT_EQUAL(n, list_interface->size(list));
    for (int i = 0; i < n; i++) {
        int *number = (int *)malloc(sizeof(int));
        *number = i;
        list_interface->add_at(list, number, i);
    }
    TEST_ASSERT_EQUAL(2 * n, list_interface->size(list));
}

void test_ArrayListGetAt(void)
{
    int n = 1000;
    for (int i = 0; i < n; i++) {
        int *number = (int *)malloc(sizeof(int));
        *number = i;
        list_interface->add_last(list, number);
    }
    TEST_ASSERT_EQUAL(n, list_interface->size(list));
    for (int i = 0; i < n; i++) {
        int *number = (int *)malloc(sizeof(int));
        *number = i;
        list_interface->add_at(list, number, i);
    }
    TEST_ASSERT_EQUAL(2 * n, list_interface->size(list));
    for (int i = 0; i < n; i++) {
        TEST_ASSERT_EQUAL(i, *((int *) list_interface->get_at(list, i)));
    }
}

void test_ArrayListRemoveAtWithEmptyList(void)
{
    bool result = list_interface->remove_at(list, 0);
    TEST_ASSERT_FALSE(result);
}

void test_ArrayListRemoveAtFromLast(void)
{
    int n = 1000;
    for (int i = 0; i < n; i++) {
        int *number = (int *)malloc(sizeof(int));
        *number = i;
        list_interface->add_last(list, number);
    }
    TEST_ASSERT_EQUAL(n, list_interface->size(list));
    for (int i = 0; i < n; i++) {
        int *number = (int *)malloc(sizeof(int));
        *number = i;
        list_interface->add_at(list, number, i);
    }
    TEST_ASSERT_EQUAL(2 * n, list_interface->size(list));
    for (size_t i = 2 * n - 1; i > 0; i--)
    {
        TEST_ASSERT_TRUE(list_interface->remove_at(list, i));
    }
}

void test_ArrayListRemoveAtFromFirst(void)
{
    int n = 1000;
    for (int i = 0; i < n; i++) {
        int *number = (int *)malloc(sizeof(int));
        *number = i;
        list_interface->add_last(list, number);
    }
    TEST_ASSERT_EQUAL(n, list_interface->size(list));
    for (int i = 0; i < n; i++) {
        int *number = (int *)malloc(sizeof(int));
        *number = i;
        list_interface->add_at(list, number, i);
    }
    TEST_ASSERT_EQUAL(2 * n, list_interface->size(list));
    for (size_t i = 0; i < 2 * n; i++)
    {
        TEST_ASSERT_TRUE(list_interface->remove_at(list, 0));
    }
}


void test_ArrayListRemoveAtRandomIndex(void)
{
    int n = 1000;
    for (int i = 0; i < n; i++) {
        int *number = (int *)malloc(sizeof(int));
        *number = i;
        list_interface->add_last(list, number);
    }
    TEST_ASSERT_EQUAL(n, list_interface->size(list));
    for (int i = 0; i < n; i++) {
        int *number = (int *)malloc(sizeof(int));
        *number = i;
        list_interface->add_at(list, number, i);
    }

    size_t size = list_interface->size(list);
    TEST_ASSERT_EQUAL(2 * n, size);
    size_t times = size;
    time_t t;

    /* Initialises random number generator */
    srand((unsigned) time(&t));

    /* Print 5 random numbers from 0 to 49 */
    for(size_t i = 0 ; i < times; i++ ) {
        size_t r = rand() % size;
        TEST_ASSERT_TRUE(list_interface->remove_at(list, r));
        size = list_interface->size(list);
    }
    TEST_ASSERT_FALSE(list_interface->remove_at(list, 0));
}


void test_ArrayListRemoveFirst(void)
{
    int n = 1000;
    for (int i = 0; i < n; i++) {
        int *number = (int *)malloc(sizeof(int));
        *number = i;
        list_interface->add_last(list, number);
    }
    TEST_ASSERT_EQUAL(n, list_interface->size(list));
    for (int i = 0; i < n; i++) {
        int *number = (int *)malloc(sizeof(int));
        *number = i;
        list_interface->add_at(list, number, i);
    }
    TEST_ASSERT_EQUAL(2 * n, list_interface->size(list));
    for (size_t i = 0; i < 2 * n; i++)
    {
        TEST_ASSERT_TRUE(list_interface->remove_first(list));
    }
}

void test_ArrayListRemoveLast(void)
{
    int n = 1000;
    for (int i = 0; i < n; i++) {
        int *number = (int *)malloc(sizeof(int));
        *number = i;
        list_interface->add_last(list, number);
    }
    TEST_ASSERT_EQUAL(n, list_interface->size(list));
    for (int i = 0; i < n; i++) {
        int *number = (int *)malloc(sizeof(int));
        *number = i;
        list_interface->add_at(list, number, i);
    }
    TEST_ASSERT_EQUAL(2 * n, list_interface->size(list));
    for (size_t i = 2 * n - 1; i > 0; i--)
    {
        TEST_ASSERT_TRUE(list_interface->remove_last(list));
    }
}

void test_ArrayListLastNode(void) {
    int n = 1000;
    for (int i = 0; i < n; i++) {
        int *number = (int *) malloc(sizeof(int));
        *number = i;
        list_interface->add_last(list, number);
    }
    TEST_ASSERT_EQUAL(n, list_interface->size(list));
    for (int i = n - 1; i >= 0; i--) {
        /**
         * This is the code being tested.
         */
        list_node_t n = list_interface->last_node(list);
        TEST_ASSERT_NOT_NULL(n);
        const void * v_returned = list_interface->node_value(list, n);
        TEST_ASSERT_NOT_NULL(v_returned);
        int k = *((int *)v_returned);
        TEST_ASSERT_EQUAL(i, k);
        list_interface->remove_last(list);
    }
}


void test_ArrayListNxGetAt(void) {
    int n = 1000;
    for (int i = 0; i < n; i++) {
        int *number = (int *) malloc(sizeof(int));
        *number = i;
        list_interface->add_last(list, number);
    }
    TEST_ASSERT_EQUAL(n, list_interface->size(list));
    for (int i = 0; i < n; i++) {
        /**
         * This is the code being tested.
         */
        list_node_t n = list_interface->nx_get_at(list, i);
        TEST_ASSERT_NOT_NULL(n);
        const void * v_returned = list_interface->node_value(list, n);
        TEST_ASSERT_NOT_NULL(v_returned);
        int k = *((int *)v_returned);
        TEST_ASSERT_EQUAL(i, k);
    }
}

void test_ArrayListPreviousNode(void) {
    int n = 1000;
    for (int i = 0; i < n; i++) {
        int *number = (int *) malloc(sizeof(int));
        *number = i;
        list_interface->add_last(list, number);
    }
    TEST_ASSERT_EQUAL(n, list_interface->size(list));

    list_node_t current_node = list_interface->last_node(list);
    TEST_ASSERT_NOT_NULL(current_node);

    for (int i = n - 1; i >= 0; i--) {
        /**
         * This is the code being tested.
         */
        list_node_t cursor_node = list_interface->previous_node(list, current_node);
        TEST_ASSERT_NOT_NULL(cursor_node);

        const void *current_node_v = list_interface->node_value(list, current_node);
        TEST_ASSERT_NOT_NULL(current_node_v);
        const void *cursor_node_v = list_interface->node_value(list, cursor_node);
        if (i > 0) {
            TEST_ASSERT_NOT_NULL(cursor_node_v);
            TEST_ASSERT_EQUAL(*((int *)current_node_v) - 1, *((int *)cursor_node_v));
            current_node = list_interface->nx_get_at(list, i);
        }
    }
}

void test_ArrayListNextNode(void) {
    int n = 1000;
    for (int i = 0; i < n; i++) {
        int *number = (int *) malloc(sizeof(int));
        *number = i;
        list_interface->add_last(list, number);
    }
    TEST_ASSERT_EQUAL(n, list_interface->size(list));

    list_node_t current_node = list_interface->first_node(list);
    TEST_ASSERT_NOT_NULL(current_node);

    for (int i = 0; i < n - 2; i++) {
        /**
         * This is the code being tested.
         */
        list_node_t cursor_node = list_interface->next_node(list, current_node);
        TEST_ASSERT_NOT_NULL(cursor_node);

        const void *current_node_v = list_interface->node_value(list, current_node);
        TEST_ASSERT_NOT_NULL(current_node_v);
        const void *cursor_node_v = list_interface->node_value(list, cursor_node);
        if (i < n - 1) {
            TEST_ASSERT_NOT_NULL(cursor_node_v);
            TEST_ASSERT_EQUAL(*((int *)current_node_v) + 1, *((int *)cursor_node_v));
            current_node = list_interface->nx_get_at(list, i);
        }
    }
}

void test_Sandbox(void)
{
    int *i = (int *)malloc(sizeof (int));
    *i = 3;
    list_interface->add_first(list, i);
    const void *result = list_interface->get_first(list);
    // Not a recommended way of doing things.
    *((int *)result) = 4;
    printf("%d\n", *((int *)list_interface->get_first(list)));
}

int main(int argc, char *argv[])
{
    UNITY_BEGIN();
    RUN_TEST(test_TrialTest);
    RUN_TEST(test_ArrayListCreateShouldNotReturnNull);
    RUN_TEST(test_ArrayListNewlyCreateShouldHaveSizeZero);
    RUN_TEST(test_ArrayListGetAtOnEmptyList);
    RUN_TEST(test_ArrayListAddFirst);
    RUN_TEST(test_ArrayListAddLast);
    RUN_TEST(test_ArrayListAddAt);
    RUN_TEST(test_ArrayListGetAt);
    RUN_TEST(test_ArrayListRemoveAtWithEmptyList);
    RUN_TEST(test_ArrayListRemoveAtFromLast);
    RUN_TEST(test_ArrayListRemoveAtFromFirst);
    RUN_TEST(test_ArrayListRemoveAtRandomIndex);
    RUN_TEST(test_ArrayListRemoveFirst);
    RUN_TEST(test_ArrayListRemoveLast);

    /**
     * Node related tests
     */
    RUN_TEST(test_ArrayListNxGetAt);
    RUN_TEST(test_ArrayListLastNode);
    RUN_TEST(test_ArrayListPreviousNode);
    RUN_TEST(test_ArrayListNextNode);

//    run();
    /**
     * Sandbox
     */
    RUN_TEST(test_Sandbox);

    return UNITY_END();
}
