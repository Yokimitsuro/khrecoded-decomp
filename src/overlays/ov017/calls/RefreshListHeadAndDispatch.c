#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x60];
    void *listHead;
} OverlayObject;

extern void *func_ov017_020a50f8();
extern void DispatchListHeadCallback(OverlayObject *obj);

void RefreshListHeadAndDispatch(OverlayObject *obj)
{
    if (obj->listHead != 0) {
        obj->listHead = func_ov017_020a50f8();
        DispatchListHeadCallback(obj);
    }
}
