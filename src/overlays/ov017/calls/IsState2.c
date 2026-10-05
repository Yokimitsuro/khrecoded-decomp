#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x4a];
    s8 state;
} OverlayObject;

BOOL IsState2(OverlayObject *obj)
{
    if (obj->state == 2) {
        return 1;
    }
    return 0;
}
