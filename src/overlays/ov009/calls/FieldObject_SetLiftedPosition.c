#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_00[0xa4];
    VecFx32 position;
} EntityBody;

typedef struct {
    u32 flags;
    EntityBody body;
} Entity;

typedef struct {
    u8 pad_00[0x38];
    u8 actorId;
    u8 pad_39[7];
    VecFx32 position;
} FieldObject;

extern Entity *ActorRegistry_GetEntityByIndex(int actorId);
extern void Obj_SetPosition(Entity *entity, const VecFx32 *position);

void FieldObject_SetLiftedPosition(FieldObject *object, const VecFx32 *position)
{
    EntityBody *body;

    object->position = *position;
    object->position.y += 0x800;
    Obj_SetPosition(ActorRegistry_GetEntityByIndex(object->actorId), &object->position);
    object->position.y -= 0x800;
    body = &ActorRegistry_GetEntityByIndex(object->actorId)->body;
    body->position = object->position;
}
