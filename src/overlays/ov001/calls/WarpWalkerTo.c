#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct Entity Entity;

typedef struct StageWalker {
    u8 pad_000[0x10];
    u8 entity[0x2b0];
    VecFx32 position;
    VecFx32 previousPosition;
} StageWalker;

extern void Obj_SetPosition(void *entity, const VecFx32 *position);

void WarpWalkerTo(StageWalker *walker, const VecFx32 *position)
{
    walker->position = *position;
    walker->previousPosition = *position;
    Obj_SetPosition(walker->entity, &walker->position);
}
