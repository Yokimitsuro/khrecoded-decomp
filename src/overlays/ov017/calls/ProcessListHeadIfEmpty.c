#include "nitro/types.h"

typedef struct ListNode {
    u8 pad_00[4];
    struct ListNode *next;
} ListNode;

typedef struct {
    u8 pad_00[0x60];
    ListNode *listHead;
} OverlayObject;

extern void AppendFieldLinkedEntry(ListNode **head);
extern void DispatchListHeadCallback(OverlayObject *obj);

void ProcessListHeadIfEmpty(OverlayObject *obj)
{
    AppendFieldLinkedEntry(&obj->listHead);
    if (obj->listHead->next == obj->listHead) {
        DispatchListHeadCallback(obj);
    }
}
