#include "nitro/types.h"

typedef struct ListNode {
    struct ListNode *next;
} ListNode;

typedef struct {
    u8 pad_00[0x404];
    ListNode *pending;
} OverlayState;

extern OverlayState *data_ov031_020bc820;

void LinkPendingNode(ListNode *node)
{
    ListNode *it;
    ListNode *head;

    head = data_ov031_020bc820->pending;

    for (it = head; it != NULL; it = it->next) {
    }
    if (head == NULL) {
        data_ov031_020bc820->pending = node;
        return;
    }
    node->next = head->next;
    data_ov031_020bc820->pending->next = node;
}

