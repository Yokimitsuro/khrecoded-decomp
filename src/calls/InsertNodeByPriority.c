#include "nitro/types.h"

typedef struct PriorityNode {
    struct PriorityNode *prev;
    struct PriorityNode *next;
    u8 pad_08[4];
    s8 priority;
} PriorityNode;

void InsertNodeByPriority(PriorityNode *node, PriorityNode **tail, PriorityNode **head)
{
    PriorityNode *cursor = *head;

    if (cursor == NULL) {
        *head = node;
        *tail = node;
        return;
    }
    while (cursor != NULL) {
        if (cursor->priority <= node->priority) {
            break;
        }
        cursor = cursor->next;
    }
    if (cursor != NULL) {
        node->next = cursor;
        node->prev = cursor->prev;
        cursor->prev = node;
        if (node->prev != NULL) {
            node->prev->next = node;
        } else {
            *head = node;
        }
        return;
    }
    if (*tail != NULL) {
        node->prev = *tail;
        (*tail)->next = node;
    }
    *tail = node;
}
