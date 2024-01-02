/****************************************************************************************************
 * Include
 ****************************************************************************************************/

#include "stack.h"

/****************************************************************************************************
 * Function Definition (Public)
 ****************************************************************************************************/

/*** Create ***/
stack_stack_t *stack_create(const stack_destroyCallback_t DestroyCallback)
{
    /*** Create ***/
    return (stack_stack_t *)list_create(DestroyCallback, NULL);
}

/*** Destroy ***/
void stack_destroy(stack_stack_t * const stack)
{
    /*** Destroy ***/
    list_destroy((list_list_t *)stack);
}

/*** Pop ***/
void *stack_pop(stack_stack_t * const stack)
{
    /*** Pop ***/
    return list_popHead((list_list_t *)stack);
}

/*** Push ***/
void stack_push(stack_stack_t * const stack, void * const data)
{
    /*** Push ***/
    list_pushHead((list_list_t *)stack, data);
}

/*** Size ***/
size_t stack_size(const stack_stack_t * const Stack)
{
    /*** Size ***/
    return list_size((const list_list_t *)Stack);
}
