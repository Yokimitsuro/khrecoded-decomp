#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef struct CollisionBox {
    VecFx32 center;
    fx32 halfExtents[3];
    VecFx32 axes[3];
    u8 flags;
} CollisionBox;

void UpdateBoxAxisAlignedFlag(CollisionBox *box)
{
    box->flags = 0;
    if (box->axes[0].x == FX32_ONE && box->axes[1].y == FX32_ONE && box->axes[2].z == FX32_ONE) {
        box->flags |= 1;
    }
}
