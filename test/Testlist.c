//
// Created by Christian Vasquez on 13/4/2023.
//
#include "../src/list.h"
#include "../unity/src/unity.h"



void setUp(void)
{
    printf("\nSet Up called.\n");
}

void tearDown(void)
{
    printf("Tear Down called.\n");
}

void test_ListHTrialTest(void)
{
    printf("test_TrialTest called.\n");
    TEST_ASSERT(true);
}


int main(int argc, char *argv[])
{
    UNITY_BEGIN();
    RUN_TEST(test_ListHTrialTest);
    return UNITY_END();
}