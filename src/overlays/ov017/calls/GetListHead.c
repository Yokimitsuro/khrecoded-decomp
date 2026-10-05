#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x60];
    void *listHead;
} OverlayObject;

typedef struct {
    u32 first;
    void *listHead;
    u32 last;
} ListHeadInfo;

BOOL GetListHead(OverlayObject *obj, ListHeadInfo *info)
{
    void *head = obj->listHead;

    info->first = 0;
    info->listHead = head;
    info->last = 0;
    return obj->listHead != 0;
}
