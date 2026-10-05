#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_00[0x40];
    VecFx32 pos;
} Actor;

extern VecFx32 *func_ov001_0206dc4c(int arg);
extern fx32 VEC_Distance(const VecFx32 *a, const VecFx32 *b);
extern void FieldObject_SetSavedValue(Actor *actor, int flag);

BOOL Actor_CheckProximityTrigger(Actor *actor)
{
    VecFx32 *target = func_ov001_0206dc4c(0);

    if (actor->pos.y <= target->y) {
        target = func_ov001_0206dc4c(0);
        if (VEC_Distance(&actor->pos, target) < 0x3000) {
            FieldObject_SetSavedValue(actor, 1);
        }
    }
    return FALSE;
}
