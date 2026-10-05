#include "nitro/types.h"

typedef struct PoolNode {
    struct PoolNode *next;
    u32 slot : 8;
    s32 action : 8;
    u32 : 9;
    s32 pending : 1;
    u32 : 6;
} PoolNode;

extern PoolNode **GetPool4Entry(void *owner, int index);

void AppendPool4Node(void *owner, int index, PoolNode *node)
{
    PoolNode **head = GetPool4Entry(owner, index);
    PoolNode *tail;

    node->next = NULL;
    node->pending = 0;
    if (*head == NULL) {
        *head = node;
        return;
    }
    tail = *head;
    while (tail->next != NULL) {
        tail = tail->next;
    }
    tail->next = node;
}
