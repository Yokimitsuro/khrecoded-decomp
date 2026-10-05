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
} HandlePool;

extern int GetEntryNumberFromAddress(HandlePool *pool, PoolNode *node);
extern void HandlePool_ReleaseHandle(HandlePool *pool, int handle);

void HandlePool_ReleaseAll(HandlePool *pool)
{
    PoolNode *node;
    PoolNode *next;

    if (pool != NULL) {
        node = pool->usedList;
        while (node != NULL) {
            next = node->next;
            HandlePool_ReleaseHandle(pool, GetEntryNumberFromAddress(pool, node));
            node = next;
        }
    }
}
