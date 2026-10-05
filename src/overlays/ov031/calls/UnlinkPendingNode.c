#include "nitro/types.h"

typedef struct ListNode {
    struct ListNode *next;
} ListNode;

typedef struct {
    u8 pad_00[0x404];
    ListNode *pending;
} OverlayState;

extern OverlayState *data_ov031_020bc820;

void UnlinkPendingNode(ListNode *node)
{
    ListNode *prev = NULL;
    ListNode *it;

    for (it = data_ov031_020bc820->pending; it != NULL; it = it->next) {
        if (it == node) {
            if (prev != NULL) {
                prev->next = node->next;
            } else {
                data_ov031_020bc820->pending = NULL;
            }
            return;
        }
        prev = it;
    }
}
