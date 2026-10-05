#include "nitro/types.h"

typedef void (*NodeCallback)(void *arg0, void *arg1, u16 arg2);

typedef struct {
    u8 pad_00[4];
    u8 *callbackTableBase;
    u8 pad_08[0x58];
    u8 *listHead;
} OverlayObject;

void DispatchListHeadCallback(OverlayObject *obj)
{
    u8 *node = obj->listHead;
    NodeCallback callback = *(NodeCallback *)(obj->callbackTableBase + (u32)*node * 4 + 0x174);

    callback((u8 *)obj + 0x70, obj, *(u16 *)(node + 2));
}
