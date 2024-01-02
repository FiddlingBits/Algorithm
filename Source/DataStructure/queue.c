/****************************************************************************************************
 * Include
 ****************************************************************************************************/

#include "queue.h"

/****************************************************************************************************
 * Function Definition (Public)
 ****************************************************************************************************/

/*** Create ***/
queue_queue_t *queue_create(const queue_destroyCallback_t DestroyCallback)
{
    /*** Create ***/
    return (queue_queue_t *)list_create(DestroyCallback, NULL);
}

/*** Dequeue ***/
void *queue_dequeue(queue_queue_t * const queue)
{
    /*** Dequeue ***/
    return list_popHead((list_list_t *)queue);
}

/*** Destroy ***/
void queue_destroy(queue_queue_t * const queue)
{
    /*** Destroy ***/
    list_destroy((list_list_t *)queue);
}

/*** Enqueue ***/
void queue_enqueue(queue_queue_t * const queue, void * const data)
{
    /*** Enqueue ***/
    list_pushTail((list_list_t *)queue, data);
}

/*** Size ***/
size_t queue_size(const queue_queue_t * const Queue)
{
    /*** Size ***/
    return list_size((const list_list_t *)Queue);
}
