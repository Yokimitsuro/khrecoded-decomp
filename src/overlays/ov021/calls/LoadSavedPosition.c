#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct PositionTarget {
    u8 pad_00[0x34];
    VecFx32 position;
} PositionTarget;

extern u8 *func_ov001_0209c3e8(void);

int LoadSavedPosition(PositionTarget *target)
{
    target->position = *(VecFx32 *)(func_ov001_0209c3e8() + 0x18e6c);
    return 0;
}
