#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_000[0x12c];
    fx32 groundHeight;
    u8 pad_130[0xe4];
    VecFx32 position;
} GroundActor;

void GetPositionAboveGround(VecFx32 *out, GroundActor *actor) {
    VecFx32 pos = actor->position;
    pos.y -= actor->groundHeight;
    *out = pos;
}
