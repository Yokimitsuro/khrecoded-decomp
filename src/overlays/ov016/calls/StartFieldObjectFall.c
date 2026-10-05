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
    u8 pad_44[0x70 - 0x44];
    u16 drawLow : 9;
    u16 drawMode : 3;
    u16 drawHigh : 4;
    u8 pad_72[0xb8 - 0x72];
    fx32 floorY;
    u8 pad_bc[0xc0 - 0xbc];
    u32 flags;
    u8 pad_c4[0xf0 - 0xc4];
    fx32 fallStartX;
    fx32 fallSpeed;
} FieldObject;

extern FieldActor *ActorRegistry_GetEntityByIndex(u32 actorId);
extern void OffsetBoxByDelta(void *src, void *dst, VecFx32 *delta);

void StartFieldObjectFall(FieldObject *obj)
{
    fx32 startX;
    FieldActor *actor;

    if (!(obj->flags & 0x100) && obj->floorY < obj->position.y) {
        obj->drawMode = 1;
        startX = obj->position.x;
        obj->fallSpeed = 0;
        obj->fallStartX = startX;
        obj->flags |= 0x100;
        {
            VecFx32 zero = {0, 0, 0};

            actor = ActorRegistry_GetEntityByIndex(obj->actorId);
            actor->delta = zero;
            OffsetBoxByDelta(actor->bounds, actor->movedBounds, &actor->delta);
        }
    }
}
