#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_00[0x38];
    u8 actorId;
    u8 pad_39[0x7];
    VecFx32 position;
} FieldObject;

extern void *ActorRegistry_GetEntityByIndex(u32 actorId);
extern void Obj_SetPosition(void *entity, const VecFx32 *position);

void SetFieldObjectPosition(FieldObject *object, const VecFx32 *position)
{
    object->position = *position;
    Obj_SetPosition(ActorRegistry_GetEntityByIndex(object->actorId), &object->position);
}
