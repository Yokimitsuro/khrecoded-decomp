#include "nitro/types.h"

typedef struct PoolNode {
    int used;
    struct PoolNode *prev;
    struct PoolNode *next;
} PoolNode;

typedef struct NodePool {
    PoolNode *nodes;
    PoolNode *freeList;
    PoolNode *usedList;
    int unk0C;
    int unk10;
    void (*onAlloc)(int, int);
} NodePool;

extern int func_ov001_0208f290(NodePool *pool, PoolNode *node);

u16 AllocPoolNode(NodePool *pool)
{
    PoolNode *node = pool->freeList;
    PoolNode *head;

    if (node == NULL) {
        return 0;
    }
    pool->freeList = node->next;
    if (node->prev != NULL) {
        node->prev->next = node->next;
    }
    if (node->next != NULL) {
        node->next->prev = node->prev;
    }
    node->prev = NULL;
    node->next = NULL;
    head = pool->usedList;
    pool->usedList = node;
    node->used = 1;
    node->prev = NULL;
    node->next = head;
    if (head != NULL) {
        head->prev = node;
    }
    if (pool->onAlloc != NULL) {
        pool->onAlloc(0, func_ov001_0208f290(pool, node));
    }
    return (u16)((u32)((u8 *)node - (u8 *)pool->nodes) / sizeof(PoolNode)) + 1;
}
