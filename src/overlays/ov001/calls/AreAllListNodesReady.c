#include "nitro/types.h"

typedef struct ListNode {
    u32 unk_00;
    struct ListNode *next;
} ListNode;

typedef struct NodeList {
    u8 pad_00[8];
    ListNode *head;
    u8 pad_0c[8];
    u8 flags;
} NodeList;

extern NodeList *data_ov001_020a04f8;
extern BOOL func_ov001_0207f530(ListNode *node);

BOOL AreAllListNodesReady(void)
{
    NodeList *list = data_ov001_020a04f8;
    BOOL ready = TRUE;
    ListNode *node = list->head;

    if (list->flags & 2) {
        while (node != NULL) {
            ListNode *next = node->next;

            if (!func_ov001_0207f530(node)) {
                ready = FALSE;
            }
            node = next;
        }
        if (ready) {
            list->flags |= 2;
        }
    }
    return ready;
}
