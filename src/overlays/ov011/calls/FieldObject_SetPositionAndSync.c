#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct FieldObject {
    u8 pad_00[0x38];
    u8 actorId;
    u8 pad_39[7];
    VecFx32 position;
} FieldObject;

extern BOOL ActorSlot_GetByIndex(int actorId);
extern void *ActorRegistry_GetEntityByIndex(int actorId);
extern void Obj_SetPosition(void *entity, const VecFx32 *position);

void FieldObject_SetPositionAndSync(FieldObject *object, const VecFx32 *position)
{
    object->position = *position;
    if (ActorSlot_GetByIndex(object->actorId)) {
        Obj_SetPosition(ActorRegistry_GetEntityByIndex(object->actorId), &object->position);
    }
}
