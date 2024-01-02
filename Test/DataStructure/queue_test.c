/****************************************************************************************************
 * Include
 ****************************************************************************************************/

#include "queue.h"
#include <stddef.h>
#include "unity_fixture.h"

/****************************************************************************************************
 * Test Group
 ****************************************************************************************************/

TEST_GROUP(queue_test);

/****************************************************************************************************
 * Test Setup
 ****************************************************************************************************/

TEST_SETUP(queue_test)
{
    UnityMalloc_StartTest();
}

/****************************************************************************************************
 * Test Tear Down
 ****************************************************************************************************/

TEST_TEAR_DOWN(queue_test)
{
    UnityMalloc_EndTest();
}

/****************************************************************************************************
 * Test Group Runner
 ****************************************************************************************************/

TEST_GROUP_RUNNER(queue_test)
{
    RUN_TEST_CASE(queue_test, create_error)
    RUN_TEST_CASE(queue_test, dequeue_error)
    RUN_TEST_CASE(queue_test, destroy)
    RUN_TEST_CASE(queue_test, destroy_error)
    RUN_TEST_CASE(queue_test, enqueue)
    RUN_TEST_CASE(queue_test, enqueue_error)
    RUN_TEST_CASE(queue_test, size_error)
}

/****************************************************************************************************
 * Test
 ****************************************************************************************************/

/*** Create ***/
/* Error */
TEST(queue_test, create_error)
{
    queue_queue_t *queue;
    
    /*** Create ***/
    /* Memory Allocation Failure */
    UnityMalloc_MakeMallocFailAfterCount(0);
    queue = queue_create(NULL);
    TEST_ASSERT_NULL(queue);
}

/*** Dequeue ***/
/* Error */
TEST(queue_test, dequeue_error)
{
    void *data;
    queue_queue_t *queue;
    
    /*** Dequeue ***/
    /* NULL Pointer */
    data = queue_dequeue(NULL);
    TEST_ASSERT_NULL(data);
    
    /* Empty */
    queue = queue_create(NULL);
    TEST_ASSERT_NOT_NULL(queue);
    data = queue_dequeue(queue);
    TEST_ASSERT_NULL(data);
    queue_destroy(queue);
}

/*** Destroy ***/
/* Success */
TEST(queue_test, destroy)
{
    void *data;
    size_t i;
    queue_queue_t *queue;
    
    /*** Destroy ***/
    /* Define */
    #define ENQUEUE_COUNT (10)
    
    /* Create */
    queue = queue_create(free);
    TEST_ASSERT_NOT_NULL(queue);
    
    /* Enqueue */
    for(i = 0; i < ENQUEUE_COUNT; i++)
    {
        data = malloc(i + 1);
        queue_enqueue(queue, data);
    }
    
    /* Destroy */
    queue_destroy(queue);
}

/* Error */
TEST(queue_test, destroy_error)
{
    /*** Destroy ***/
    /* NULL Pointer */
    queue_destroy(NULL);
}

/*** Enqueue ***/
/* Success */
TEST(queue_test, enqueue)
{
    void *dequeuedData;
    size_t i;
    queue_queue_t *queue;
    
    /*** Test Data ***/
    /* Define */
    #define ENQUEUE_COUNT (10)
    
    /* Test Data */
    void *enqueueData[ENQUEUE_COUNT];
    for(i = 0; i < ENQUEUE_COUNT; i++)
        enqueueData[i] = (void *)i;
    
    /*** Enqueue ***/
    /* Create */
    queue = queue_create(NULL);
    TEST_ASSERT_NOT_NULL(queue);
    
    /* Enqueue */
    for(i = 0; i < ENQUEUE_COUNT; i++)
    {
        queue_enqueue(queue, enqueueData[i]);
        TEST_ASSERT_EQUAL_UINT((i + 1), queue_size(queue));
    }
    
    /* Dequeue */
    for(i = 0; i < ENQUEUE_COUNT; i++)
    {
        dequeuedData = queue_dequeue(queue);
        TEST_ASSERT_EQUAL_UINT(enqueueData[i], dequeuedData); // First In, First Out
        TEST_ASSERT_EQUAL_UINT(ENQUEUE_COUNT - (i + 1), queue_size(queue));
    }
    
    /* Destroy */
    queue_destroy(queue);
}

/* Error */
TEST(queue_test, enqueue_error)
{
    queue_queue_t *queue;
    
    /*** Enqueue ***/
    /* NULL Pointer */
    queue_enqueue(NULL, (void *)0);
    
    /* Memory Allocation Failure */
    UnityMalloc_MakeMallocFailAfterCount(1);
    queue = queue_create(NULL);
    TEST_ASSERT_NOT_NULL(queue);
    queue_enqueue(queue, (void *)0);
    TEST_ASSERT_EQUAL_UINT(0, queue_size(queue)); // No Change
    queue_destroy(queue);
}

/*** Size ***/
/* Error */
TEST(queue_test, size_error)
{
    /*** Size ***/
    /* NULL Pointer */
    TEST_ASSERT_EQUAL_UINT(0, queue_size(NULL));
}
