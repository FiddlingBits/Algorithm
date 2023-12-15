/****************************************************************************************************
 * Include
 ****************************************************************************************************/

#include "list.h"
#include <stdbool.h>
#include <stddef.h>
#include "unity_fixture.h"

/****************************************************************************************************
 * Test Group
 ****************************************************************************************************/

TEST_GROUP(list_test);

/****************************************************************************************************
 * Test Setup
 ****************************************************************************************************/

TEST_SETUP(list_test)
{
    UnityMalloc_StartTest();
}

/****************************************************************************************************
 * Test Tear Down
 ****************************************************************************************************/

TEST_TEAR_DOWN(list_test)
{
    UnityMalloc_EndTest();
}

/****************************************************************************************************
 * Test Group Runner
 ****************************************************************************************************/

TEST_GROUP_RUNNER(list_test)
{
    RUN_TEST_CASE(list_test, create_error)
    RUN_TEST_CASE(list_test, destroy)
    RUN_TEST_CASE(list_test, destroy_error)
    RUN_TEST_CASE(list_test, match)
    RUN_TEST_CASE(list_test, match_error)
    RUN_TEST_CASE(list_test, peek)
    RUN_TEST_CASE(list_test, peek_error)
    RUN_TEST_CASE(list_test, popHead_error)
    RUN_TEST_CASE(list_test, pushHead)
    RUN_TEST_CASE(list_test, pushHead_error)
    RUN_TEST_CASE(list_test, pushTail)
    RUN_TEST_CASE(list_test, pushTail_error)
    RUN_TEST_CASE(list_test, size_error)
}

/****************************************************************************************************
 * Test
 ****************************************************************************************************/

/*** Create ***/
/* Error */
TEST(list_test, create_error)
{
    list_list_t *list;
    
    /*** Create ***/
    /* Memory Allocation Failure */
    UnityMalloc_MakeMallocFailAfterCount(0);
    list = list_create(NULL, NULL);
    TEST_ASSERT_NULL(list);
}

/*** Destroy ***/
/* Success */
TEST(list_test, destroy)
{
    void *pushedData;
    size_t i;
    list_list_t *list;
    
    /*** Destroy ***/
    /* Define */
    #define PUSH_COUNT (10)
    
    /* Create */
    list = list_create(free, NULL);
    TEST_ASSERT_NOT_NULL(list);
    
    /* Push Head/Tail */
    for(i = 0; i < PUSH_COUNT; i++)
    {
        pushedData = malloc(i + 1);
        if((i % 2) == 0)
            list_pushHead(list, pushedData);
        else
            list_pushTail(list, pushedData);
    }
    
    /* Destroy */
    list_destroy(list);
}

/* Error */
TEST(list_test, destroy_error)
{
    /*** Destroy ***/
    /* NULL Pointer */
    list_destroy(NULL);
}

/*** Match ***/
/* Callback */
static bool listTest_matchCallback(const void * const Data1, const void * const Data2)
{
    /*** Match ***/
    return (Data1 == Data2);
}

/* Success */
TEST(list_test, match)
{
    size_t i;
    list_list_t *list;
    
    /*** Test Data ***/
    /* Define */
    #define PUSH_COUNT (10)
    
    /* Test Data */
    void *pushData[PUSH_COUNT];
    for(i = 0; i < PUSH_COUNT; i++)
        pushData[i] = (void *)i;
    
    /*** Match ***/    
    /* Create */
    list = list_create(NULL, listTest_matchCallback);
    TEST_ASSERT_NOT_NULL(list);
    
    /* Push Head/Tail */
    for(i = 0; i < PUSH_COUNT; i++)
    {
        if((i % 2) == 0)
            list_pushHead(list, pushData[i]);
        else
            list_pushTail(list, pushData[i]);
    }
    
    /* Match */
    TEST_ASSERT_TRUE(list_match(list, (void *)0));
    TEST_ASSERT_TRUE(list_match(list, (void *)(PUSH_COUNT - 1)));
    TEST_ASSERT_FALSE(list_match(list, (void *)PUSH_COUNT));
    
    /* Destroy */
    list_destroy(list);
}

/* Error */
TEST(list_test, match_error)
{
    list_list_t *list;
    
    /*** Match ***/
    /* Empty */
    list = list_create(NULL, listTest_matchCallback);
    TEST_ASSERT_NOT_NULL(list);
    TEST_ASSERT_FALSE(list_match(list, (void *)0));
    list_destroy(list);
    
    /* NULL Pointer */
    list = list_create(NULL, listTest_matchCallback);
    TEST_ASSERT_NOT_NULL(list);
    TEST_ASSERT_FALSE(list_match(NULL, (void *)0));
    TEST_ASSERT_FALSE(list_match(list, (void *)0));
    list_destroy(list);
}

/*** Peek ***/
/* Success */
TEST(list_test, peek)
{
    size_t i;
    list_list_t *list;
    void *peekedData;
    
    /*** Test Data ***/
    /* Define */
    #define PUSH_COUNT (10)
    
    /* Test Data */
    void *pushData[PUSH_COUNT];
    for(i = 0; i < PUSH_COUNT; i++)
        pushData[i] = (void *)i;
    
    /*** Peek ***/
    /* Create */
    list = list_create(NULL, NULL);
    TEST_ASSERT_NOT_NULL(list);
    
    /* Push Data To Tail */
    for(i = 0; i < PUSH_COUNT; i++)
    {
        list_pushTail(list, pushData[i]);
        TEST_ASSERT_EQUAL_UINT((i + 1), list_size(list));
    }
    
    /* Peek */
    for(i = 0; i < PUSH_COUNT; i++)
    {
        peekedData = list_peek(list, i);
        TEST_ASSERT_EQUAL_UINT(pushData[i], peekedData); // First In, First Out
        TEST_ASSERT_EQUAL_UINT(PUSH_COUNT, list_size(list)); // Doesn't Change
    }
    
    /* Destroy */
    list_destroy(list);
}

/* Error */
TEST(list_test, peek_error)
{
    void *peekedData, *pushedData;
    size_t i;
    list_list_t *list;
    
    /*** Destroy ***/
    /* Define */
    #define PUSH_COUNT (10)
    
    /* Create */
    list = list_create(free, NULL);
    TEST_ASSERT_NOT_NULL(list);
    
    /* Push Head/Tail */
    for(i = 0; i < PUSH_COUNT; i++)
    {
        pushedData = malloc(i + 1);
        if((i % 2) == 0)
            list_pushHead(list, pushedData);
        else
            list_pushTail(list, pushedData);
    }
    
    /* NULL Pointer */
    peekedData = list_peek(NULL, 0);
    TEST_ASSERT_NULL(peekedData);
    
    /* Out Of Range */
    peekedData = list_peek(list, PUSH_COUNT);
    TEST_ASSERT_NULL(peekedData);
    
    /* Destroy */
    list_destroy(list);
}

/*** Pop Data From Head ***/
/* Error */
TEST(list_test, popHead_error)
{
    void *poppedData;
    list_list_t *list;
    
    /*** Pop Data From Head ***/
    /* NULL Pointer */
    poppedData = list_popHead(NULL);
    TEST_ASSERT_NULL(poppedData);
    
    /* Empty */
    list = list_create(NULL, NULL);
    TEST_ASSERT_NOT_NULL(list);
    poppedData = list_popHead(list);
    TEST_ASSERT_NULL(poppedData);
    list_destroy(list);
}

/*** Push Data To Head ***/
/* Success */
TEST(list_test, pushHead)
{
    void *poppedData;
    size_t i;
    list_list_t *list;
    
    /*** Test Data ***/
    /* Define */
    #define PUSH_COUNT (10)
    
    /* Test Data */
    void *pushData[PUSH_COUNT];
    for(i = 0; i < PUSH_COUNT; i++)
        pushData[i] = (void *)i;
    
    /*** Push Data To Head ***/
    /* Create */
    list = list_create(NULL, NULL);
    TEST_ASSERT_NOT_NULL(list);
    
    /* Push Data To Head */
    for(i = 0; i < PUSH_COUNT; i++)
    {
        list_pushHead(list, pushData[i]);
        TEST_ASSERT_EQUAL_UINT((i + 1), list_size(list));
    }
    
    /* Pop Data From Head */
    for(i = 0; i < PUSH_COUNT; i++)
    {
        poppedData = list_popHead(list);
        TEST_ASSERT_EQUAL_UINT(pushData[PUSH_COUNT - (i + 1)], poppedData); // Last In, First Out
        TEST_ASSERT_EQUAL_UINT(PUSH_COUNT - (i + 1), list_size(list));
    }
    
    /* Destroy */
    list_destroy(list);
}

/* Error */
TEST(list_test, pushHead_error)
{
    list_list_t *list;
    
    /*** Push Data To Head ***/
    /* NULL Pointer */
    list_pushHead(NULL, (void *)0);
    
    /* Memory Allocation Failure */
    UnityMalloc_MakeMallocFailAfterCount(1);
    list = list_create(NULL, NULL);
    TEST_ASSERT_NOT_NULL(list);
    list_pushHead(list, (void *)0);
    TEST_ASSERT_EQUAL_UINT(0, list_size(list)); // No Change
    list_destroy(list);
}

/*** Push Data To Tail ***/
/* Success */
TEST(list_test, pushTail)
{
    void *poppedData;
    size_t i;
    list_list_t *list;
    
    /*** Test Data ***/
    /* Define */
    #define PUSH_COUNT (10)
    
    /* Test Data */
    void *pushData[PUSH_COUNT];
    for(i = 0; i < PUSH_COUNT; i++)
        pushData[i] = (void *)i;
    
    /*** Push Data To Tail ***/
    /* Create */
    list = list_create(NULL, NULL);
    TEST_ASSERT_NOT_NULL(list);
    
    /* Push Data To Tail */
    for(i = 0; i < PUSH_COUNT; i++)
    {
        list_pushTail(list, pushData[i]);
        TEST_ASSERT_EQUAL_UINT((i + 1), list_size(list));
    }
    
    /* Pop Data From Head */
    for(i = 0; i < PUSH_COUNT; i++)
    {
        poppedData = list_popHead(list);
        TEST_ASSERT_EQUAL_UINT(pushData[i], poppedData); // First In, First Out
        TEST_ASSERT_EQUAL_UINT(PUSH_COUNT - (i + 1), list_size(list));
    }
    
    /* Destroy */
    list_destroy(list);
}

/* Error */
TEST(list_test, pushTail_error)
{
    list_list_t *list;
    
    /*** Push Data To Tail ***/
    /* NULL Pointer */
    list_pushTail(NULL, (void *)0);
    
    /* Memory Allocation Failure */
    UnityMalloc_MakeMallocFailAfterCount(1);
    list = list_create(NULL, NULL);
    TEST_ASSERT_NOT_NULL(list);
    list_pushTail(list, (void *)0);
    TEST_ASSERT_EQUAL_UINT(0, list_size(list)); // No Change
    list_destroy(list);
}

/*** Size ***/
/* Error */
TEST(list_test, size_error)
{
    /*** Size ***/
    /* NULL Pointer */
    TEST_ASSERT_EQUAL_UINT(0, list_size(NULL));
}
