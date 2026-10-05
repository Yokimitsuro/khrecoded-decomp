#include "nitro/types.h"

typedef struct PoolNode {
    u32 flags;
    struct PoolNode *prev;
    struct PoolNode *next;
} PoolNode;

typedef struct HandlePool {
    PoolNode *nodes;
    PoolNode *freeList;
    PoolNode *usedList;
    u8 *elements;
    u16 elementSize;
    u16 pad_12;
    void (*callback)(int event, void *element);
} HandlePool;

extern void *func_ov001_0208f280(HandlePool *pool, int handle);

void HandlePool_ReleaseHandle(HandlePool *pool, int handle)
{
    PoolNode *node;
    PoolNode *head;

    node = &pool->nodes[(u16)(handle - 1)];
    if (node->flags & 1) {
        if (pool->callback != NULL) {
            pool->callback(1, func_ov001_0208f280(pool, handle));
        }
        if (node != NULL) {
            if (pool->freeList == node) {
                pool->freeList = pool->freeList->next;
            }
            if (pool->usedList == node) {
                pool->usedList = pool->usedList->next;
            }
            if (node->prev != NULL) {
                node->prev->next = node->next;
            }
            if (node->next != NULL) {
                node->next->prev = node->prev;
            }
            node->prev = NULL;
            node->next = NULL;
        }
        head = pool->freeList;
        pool->freeList = node;
        node->flags = 0;
        node->prev = NULL;
        node->next = head;
        if (head != NULL) {
            head->prev = node;
        }
    }
}
