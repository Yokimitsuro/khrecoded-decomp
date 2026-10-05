#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct LinkedActorObject {
    u8 pad_00[0x18];
    u8 shape[0x20];
    u8 actorId;
    u8 pad_39[7];
    VecFx32 position;
} LinkedActorObject;

extern void *ActorRegistry_GetEntityByIndex(u32 id);
extern void Obj_SetPosition(void *entity, const VecFx32 *position);
extern void SetShapePosition(void *shape, const VecFx32 *position);

void MoveLinkedActor(LinkedActorObject *object, const VecFx32 *position)
{
    object->position = *position;
    Obj_SetPosition(ActorRegistry_GetEntityByIndex(object->actorId), &object->position);
    SetShapePosition(object->shape, &object->position);
}
