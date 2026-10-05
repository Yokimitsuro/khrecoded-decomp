#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_00[0x98];
    VecFx32 target;
    u8 pad_A4[0x10];
    u16 hasTarget;
} MoverState;

void SetTargetPosition_020a1b84(MoverState *mover, const VecFx32 *target) {
    mover->target = *target;
    mover->hasTarget = 1;
}
