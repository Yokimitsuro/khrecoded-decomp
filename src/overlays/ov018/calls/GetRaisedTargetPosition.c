#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_00[0x38];
    VecFx32 position;
    u8 pad_44[0xc];
    u16 flags;
    s8 state;
    u8 pad_53[5];
    VecFx32 target;
} Obj;

VecFx32 *GetRaisedTargetPosition(Obj *obj)
{
    if (!(obj->flags & 8) && obj->state == 0) {
        obj->target = obj->position;
        obj->target.y += 0x600;
        return &obj->target;
    }
    return NULL;
}
