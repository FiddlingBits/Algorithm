/****************************************************************************************************
 * Pragma
 ****************************************************************************************************/

#pragma once

/****************************************************************************************************
 * Include
 ****************************************************************************************************/

#include "list.h"
#include <stddef.h>

/****************************************************************************************************
 * Type Definition
 ****************************************************************************************************/

typedef void (*stack_destroyCallback_t)(void *data);
typedef struct stack_stack_s stack_stack_t;

/****************************************************************************************************
 * Function Prototype
 ****************************************************************************************************/

extern stack_stack_t *stack_create(const stack_destroyCallback_t DestroyCallback);
extern void stack_destroy(stack_stack_t * const stack);
extern void *stack_pop(stack_stack_t * const stack);
extern void stack_push(stack_stack_t * const stack, void * const data);
extern size_t stack_size(const stack_stack_t * const Stack);
