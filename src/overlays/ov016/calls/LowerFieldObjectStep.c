#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_000[0x134];
    u8 bounds[0x18];
    u8 pad_14c[4];
    VecFx32 delta;
    u8 movedBounds[0x18];
} FieldActor;

typedef struct {
    u8 pad_00[0x32];
    u8 actorId;
    u8 pad_33[0x38 - 0x33];
    VecFx32 position;
    u8 pad_44[0xc0 - 0x44];
    u32 flags;
    u8 pad_c4[0xec - 0xc4];
    fx32 height;
} FieldObject;

extern const VecFx32 data_ov016_020a6e24;
extern const VecFx32 data_0205344c;
extern FieldActor *ActorRegistry_GetEntityByIndex(u32 actorId);
extern void OffsetBoxByDelta(void *src, void *dst, VecFx32 *delta);
extern void Obj_SetPosition(FieldActor *actor, const VecFx32 *position);
extern void func_ov016_020a2578(FieldObject *obj);

void LowerFieldObjectStep(FieldObject *obj)
{
    FieldActor *actor = ActorRegistry_GetEntityByIndex(obj->actorId);
    VecFx32 lift;
    VecFx32 position;

    if (obj->flags & 2) {
        lift = data_ov016_020a6e24;
        position = obj->position;
        position.y += lift.y;
        if (position.y <= obj->height) {
            position.y = obj->height;
            obj->flags &= ~2;
        }
        actor->delta = lift;
        OffsetBoxByDelta(actor->bounds, actor->movedBounds, &actor->delta);
        Obj_SetPosition(actor, &position);
        obj->position = position;
        func_ov016_020a2578(obj);
        return;
    }
    actor->delta = data_0205344c;
    OffsetBoxByDelta(actor->bounds, actor->movedBounds, &actor->delta);
}
