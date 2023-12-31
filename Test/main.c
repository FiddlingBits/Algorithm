/****************************************************************************************************
 * Include
 ****************************************************************************************************/

#include <stdio.h>
#include "unity_fixture.h"

/****************************************************************************************************
 * Function Prototype
 ****************************************************************************************************/

static void main_runTestGroups(void);

/****************************************************************************************************
 * Function Definition (Public)
 ****************************************************************************************************/

/*** Main Entry ***/
int main(int argc, const char *argv[])
{
    /*** Start Unity ***/
    (void)printf("Unity Version: %u.%u.%u\n", UNITY_VERSION_MAJOR, UNITY_VERSION_MINOR, UNITY_VERSION_BUILD);
    return UnityMain(argc, argv, main_runTestGroups);
}

/****************************************************************************************************
 * Function Definition (Private)
 ****************************************************************************************************/

/*** Run Test Groups ***/
static void main_runTestGroups(void)
{
    /*** Run Test Groups ***/
    RUN_TEST_GROUP(list_test)
    RUN_TEST_GROUP(queue_test)
    RUN_TEST_GROUP(stack_test)
}
