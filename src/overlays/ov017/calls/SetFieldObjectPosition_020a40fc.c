#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct FieldObject {
    u8 pad_00[0x32];
    u8 actorId;
    u8 pad_33[5];
    VecFx32 position;
} FieldObject;

extern void *ActorRegistry_GetEntityByIndex(u32 actorId);
extern void Obj_SetPosition(void *entity, const VecFx32 *position);

void SetFieldObjectPosition_020a40fc(FieldObject *object, const VecFx32 *position)
{
    object->position = *position;
    Obj_SetPosition(ActorRegistry_GetEntityByIndex(object->actorId), position);
}
