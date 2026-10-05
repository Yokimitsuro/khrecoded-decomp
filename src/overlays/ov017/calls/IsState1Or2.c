#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x4a];
    s8 state;
} OverlayObject;

BOOL IsState1Or2(OverlayObject *obj)
{
    return obj->state == 2 || obj->state == 1;
}
