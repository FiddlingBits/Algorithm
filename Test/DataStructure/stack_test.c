/****************************************************************************************************
 * Include
 ****************************************************************************************************/

#include "stack.h"
#include <stddef.h>
#include "unity_fixture.h"

/****************************************************************************************************
 * Test Group
 ****************************************************************************************************/

TEST_GROUP(stack_test);

/****************************************************************************************************
 * Test Setup
 ****************************************************************************************************/

TEST_SETUP(stack_test)
{
    UnityMalloc_StartTest();
}

/****************************************************************************************************
 * Test Tear Down
 ****************************************************************************************************/

TEST_TEAR_DOWN(stack_test)
{
    UnityMalloc_EndTest();
}

/****************************************************************************************************
 * Test Group Runner
 ****************************************************************************************************/

TEST_GROUP_RUNNER(stack_test)
{
    RUN_TEST_CASE(stack_test, create_error)
    RUN_TEST_CASE(stack_test, destroy)
    RUN_TEST_CASE(stack_test, destroy_error)
    RUN_TEST_CASE(stack_test, pop_error)
    RUN_TEST_CASE(stack_test, push)
    RUN_TEST_CASE(stack_test, push_error)
    RUN_TEST_CASE(stack_test, size_error)
}

/****************************************************************************************************
 * Test
 ****************************************************************************************************/

/*** Create ***/
/* Error */
TEST(stack_test, create_error)
{
    stack_stack_t *stack;
    
    /*** Create ***/
    /* Memory Allocation Failure */
    UnityMalloc_MakeMallocFailAfterCount(0);
    stack = stack_create(NULL);
    TEST_ASSERT_NULL(stack);
}

/*** Destroy ***/
/* Success */
TEST(stack_test, destroy)
{
    void *data;
    size_t i;
    stack_stack_t *stack;
    
    /*** Destroy ***/
    /* Define */
    #define PUSH_COUNT (10)
    
    /* Create */
    stack = stack_create(free);
    TEST_ASSERT_NOT_NULL(stack);
    
    /* Push */
    for(i = 0; i < PUSH_COUNT; i++)
    {
        data = malloc(i + 1);
        stack_push(stack, data);
    }
    
    /* Destroy */
    stack_destroy(stack);
}

/* Error */
TEST(stack_test, destroy_error)
{
    /*** Destroy ***/
    /* NULL Pointer */
    stack_destroy(NULL);
}

/*** Pop ***/
/* Error */
TEST(stack_test, pop_error)
{
    void *data;
    stack_stack_t *stack;
    
    /*** Pop ***/
    /* NULL Pointer */
    data = stack_pop(NULL);
    TEST_ASSERT_NULL(data);
    
    /* Empty */
    stack = stack_create(NULL);
    TEST_ASSERT_NOT_NULL(stack);
    data = stack_pop(stack);
    TEST_ASSERT_NULL(data);
    stack_destroy(stack);
}

/*** Push ***/
/* Success */
TEST(stack_test, push)
{
    void *poppedData;
    size_t i;
    stack_stack_t *stack;
    
    /*** Test Data ***/
    /* Define */
    #define PUSH_COUNT (10)
    
    /* Test Data */
    void *pushData[PUSH_COUNT];
    for(i = 0; i < PUSH_COUNT; i++)
        pushData[i] = (void *)i;
    
    /*** Push ***/
    /* Create */
    stack = stack_create(NULL);
    TEST_ASSERT_NOT_NULL(stack);
    
    /* Push */
    for(i = 0; i < PUSH_COUNT; i++)
    {
        stack_push(stack, pushData[i]);
        TEST_ASSERT_EQUAL_UINT((i + 1), stack_size(stack));
    }
    
    /* Pop */
    for(i = 0; i < PUSH_COUNT; i++)
    {
        poppedData = stack_pop(stack);
        TEST_ASSERT_EQUAL_UINT(pushData[PUSH_COUNT - (i + 1)], poppedData); // Last In, First Out
        TEST_ASSERT_EQUAL_UINT(PUSH_COUNT - (i + 1), stack_size(stack));
    }
    
    /* Destroy */
    stack_destroy(stack);
}

/* Error */
TEST(stack_test, push_error)
{
    stack_stack_t *stack;
    
    /*** Push ***/
    /* NULL Pointer */
    stack_push(NULL, (void *)0);
    
    /* Memory Allocation Failure */
    UnityMalloc_MakeMallocFailAfterCount(1);
    stack = stack_create(NULL);
    TEST_ASSERT_NOT_NULL(stack);
    stack_push(stack, (void *)0);
    TEST_ASSERT_EQUAL_UINT(0, stack_size(stack)); // No Change
    stack_destroy(stack);
}

/*** Size ***/
/* Error */
TEST(stack_test, size_error)
{
    /*** Size ***/
    /* NULL Pointer */
    TEST_ASSERT_EQUAL_UINT(0, stack_size(NULL));
}
