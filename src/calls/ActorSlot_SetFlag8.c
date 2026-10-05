#include "nitro/types.h"

typedef struct {
    u8 pad_00[8];
    u16 flags;
} ActorSlot;

void ActorSlot_SetFlag8(ActorSlot *slot, BOOL enable)
{
    if (enable) {
        slot->flags |= 8;
    } else {
        slot->flags &= ~8;
    }
}
