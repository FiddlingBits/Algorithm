/****************************************************************************************************
 * Include
 ****************************************************************************************************/

#include "list.h"

/****************************************************************************************************
 * Type Definition
 ****************************************************************************************************/

typedef struct list_node_s
{
	void *data;
    struct list_node_s *next;
} list_node_t;

typedef struct list_list_s
{
    list_destroyCallback_t destroyCallback;
    list_node_t *head, *tail;
    list_matchCallback_t matchCallback;
    size_t size;
} list_list_t;

/****************************************************************************************************
 * Function Definition (Public)
 ****************************************************************************************************/

/*** Create ***/
list_list_t *list_create(const list_destroyCallback_t DestroyCallback, const list_matchCallback_t MatchCallback)
{
    list_list_t *list;
    
    /*** Create ***/
    /* Allocate Memory */
    list = malloc(sizeof(*list));
    
    /* Initialize */
    if(list != NULL)
    {
        list->destroyCallback = DestroyCallback;
        list->head = list->tail = NULL;
        list->matchCallback = MatchCallback;
        list->size = 0;
    }
    
    return list;
}

/*** Destroy ***/
void list_destroy(list_list_t * const list)
{
    void *data;
    
    /*** Destroy ***/
    if(list != NULL)
    {
        /* Pop Data From Head Until Empty */
        while(list->size > 0)
        {
            data = list_popHead(list);
            if(list->destroyCallback != NULL)
                list->destroyCallback(data);
        }
        
        /* Clean Up */
        free(list);
    }
}

/*** Match ***/
bool list_match(const list_list_t * const List, const void * const Data)
{
    bool matched = false;
    const list_node_t *Node;
    
    /*** Match ***/
    if((List != NULL) && (List->matchCallback != NULL))
    {
        /* Start At Head */
        Node = List->head;
        
        /* Match */
        while(Node != NULL)
        {
            /* Check For Match */
            if(List->matchCallback(Data, Node->data))
            {
                matched = true;
                break;
            }
            
            /* Go To Next Node */
            Node = Node->next;
        }
    }
    
    return matched;
}

/*** Peek ***/
void *list_peek(const list_list_t * const List, const size_t Index)
{
    size_t i;
    const list_node_t *Node;
    
    /*** Peek ***/
    /* Error Check */
    if((List == NULL) || (Index >= List->size))
        return NULL;
    
    /* Peek */
    Node = List->head;
    for(i = 0; i < Index; i++)
        Node = Node->next;
    
    return Node->data;
}

/*** Pop Data From Head ***/
void *list_popHead(list_list_t * const list)
{
    void *data;
    list_node_t *oldHead;
    
    /*** Pop Data From Head ***/
    /* Error Check */
    if((list == NULL) || (list->size == 0))
        return NULL;
    
    /* Pop Data From Head */
    data = list->head->data;
    
    /* Update Head */
    oldHead = list->head;
    list->head = list->head->next;
    
    /* Clean Up */
    free(oldHead);
    
    /* Decrement Size */
    list->size--;
    if(list->size == 0)
    {
        /* Empty */
        list->head = NULL;
        list->tail = NULL;
    }
    
    return data;
}

/*** Push Data To Head ***/
void list_pushHead(list_list_t * const list, void * const data)
{
    list_node_t *node;
    
    /*** Push Data To Head ***/
    /* Error Check */
    if(list == NULL)
        return;
    
    /* Allocate Memory */
    node = malloc(sizeof(*node));
    if(node == NULL)
        return;
    
    /* Initialize */
    node->data = data;
    node->next = list->head; // Next Is Former Head
    
    /* Push Data To Head */
    list->head = node; // Node Is New Head
    if(list->tail == NULL)
        list->tail = node; // Node Is Head And Tail
    
    /* Increment Size */
    list->size++;
}

/*** Push Data To Tail ***/
void list_pushTail(list_list_t * const list, void * const data)
{
    list_node_t *node;
    
    /*** Push Data To Tail ***/
    /* Error Check */
    if(list == NULL)
        return;
    
    /* Allocate Memory */
    node = malloc(sizeof(*node));
    if(node == NULL)
        return;
    
    /* Initialize */
    node->data = data;
    node->next = NULL; // Element Is New Tail
    
    /* Push Data To Tail */
    if(list->tail == NULL)
        list->head = node; // List Is Empty; Node Is Head And Tail
    else
        list->tail->next = node; // Former Tail Is Second To End
    list->tail = node; // Node Is New Tail
    
    /* Increment Size */
    list->size++;
}

/*** Size ***/
size_t list_size(const list_list_t * const List)
{
    /*** Size ***/
    /* Error Check */
    if(List == NULL)
        return 0;
    else
        return List->size;
}
