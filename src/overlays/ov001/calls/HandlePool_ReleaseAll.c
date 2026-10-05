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

extern int func_ov001_0208f268(HandlePool *pool, PoolNode *node);
extern void func_ov001_0208f1d0(HandlePool *pool, int handle);

void HandlePool_ReleaseAll(HandlePool *pool)
{
    PoolNode *node;
    PoolNode *next;

    if (pool != NULL) {
        node = pool->usedList;
        while (node != NULL) {
            next = node->next;
            func_ov001_0208f1d0(pool, func_ov001_0208f268(pool, node));
            node = next;
        }
    }
}
