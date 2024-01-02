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

typedef void (*queue_destroyCallback_t)(void *data);
typedef struct queue_queue_s queue_queue_t;

/****************************************************************************************************
 * Function Prototype
 ****************************************************************************************************/

extern queue_queue_t *queue_create(const queue_destroyCallback_t DestroyCallback);
extern void *queue_dequeue(queue_queue_t * const queue);
extern void queue_destroy(queue_queue_t * const queue);
extern void queue_enqueue(queue_queue_t * const queue, void * const data);
extern size_t queue_size(const queue_queue_t * const Queue);
