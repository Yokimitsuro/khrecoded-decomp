#include "nitro/types.h"

typedef struct MessageNode {
    u8 type;
    u8 flags;
    u8 pad_02[2];
    struct MessageNode *next;
} MessageNode;

typedef struct MessageOwner {
    u8 pad_00[0x60];
    MessageNode *head;
} MessageOwner;

extern void NNSi_FndFreeFromDefaultHeap(void *ptr);

void DiscardMessageNodes(MessageOwner *owner, BOOL keepPinned)
{
    MessageNode *node;
    BOOL last;

    while ((node = owner->head) != NULL && !(node->flags & 1)) {
        owner->head = node->next;
        if (!keepPinned || (node->flags & 4)) {
            NNSi_FndFreeFromDefaultHeap(node);
        } else if (node->next != NULL && (node->next->flags & 4)) {
            node->next = NULL;
        }
    }
    if (node == NULL) {
        return;
    }
    while ((node = owner->head) != NULL && !(node->flags & 2)) {
        owner->head = node->next;
    }
    node = node->next;
    owner->head = node;
    while (node != NULL) {
        if (node->flags & 2) {
            last = TRUE;
        } else {
            last = FALSE;
        }
        owner->head = node->next;
        if (!keepPinned || (node->flags & 4)) {
            NNSi_FndFreeFromDefaultHeap(node);
        } else if (node->next != NULL && (node->next->flags & 4)) {
            node->next = NULL;
        }
        if (last) {
            return;
        }
        node = owner->head;
    }
}
