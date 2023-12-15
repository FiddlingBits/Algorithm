/****************************************************************************************************
 * Pragma
 ****************************************************************************************************/

#pragma once

/****************************************************************************************************
 * Include
 ****************************************************************************************************/

#include "project.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

/****************************************************************************************************
 * Type Definition
 ****************************************************************************************************/

typedef void (*list_destroyCallback_t)(void *data);
typedef struct list_list_s list_list_t;
typedef bool (*list_matchCallback_t)(const void * const Data1, const void * const Data2);

/****************************************************************************************************
 * Function Prototype
 ****************************************************************************************************/

extern list_list_t *list_create(const list_destroyCallback_t DestroyCallback, const list_matchCallback_t MatchCallback);
extern void list_destroy(list_list_t * const list);
extern bool list_match(const list_list_t * const List, const void * const Data);
extern void *list_peek(const list_list_t * const List, const size_t Index);
extern void *list_popHead(list_list_t * const list);
extern void list_pushHead(list_list_t * const list, void * const data);
extern void list_pushTail(list_list_t * const list, void * const data);
extern size_t list_size(const list_list_t * const List);
