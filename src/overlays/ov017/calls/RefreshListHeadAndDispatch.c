#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x60];
    void *listHead;
} OverlayObject;

extern void *GetLinkedEntryAfterTail(void *entry);
extern void DispatchListHeadCallback(OverlayObject *obj);

void RefreshListHeadAndDispatch(OverlayObject *obj)
{
    if (obj->listHead != 0) {
        obj->listHead = GetLinkedEntryAfterTail(obj->listHead);
        DispatchListHeadCallback(obj);
    }
}
