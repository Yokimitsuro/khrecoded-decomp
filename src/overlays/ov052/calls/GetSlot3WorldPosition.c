#include "nitro/types.h"
#include "nitro/fx_types.h"

extern VecFx32 GetAttachmentWorldPosition(void *actor, int slot);

VecFx32 GetSlot3WorldPosition(void *actor)
{
    return GetAttachmentWorldPosition(actor, 3);
}
