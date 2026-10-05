#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    fx32 min[3];
    fx32 max[3];
} Box;

typedef struct {
    u32 unk_00;
    Box localBounds;
    u32 unk_1c;
    VecFx32 position;
    Box bounds;
} CollisionShape;

typedef struct {
    u8 pad_000[0x140];
    CollisionShape shape;
} ActorBody;

typedef struct {
    u8 pad_00[0xc];
    ActorBody *body;
    u8 pad_10[0x38 - 0x10];
    u8 slotIndex;
    u8 pad_39[0x40 - 0x39];
    VecFx32 position;
    u8 pad_4c[0x67 - 0x4c];
    u8 highlighted : 1;
} FieldActor;

typedef struct {
    u8 pad_0000[0x214];
    u32 flags;
} FieldState;

extern FieldState *data_ov001_020a0480;

extern BOOL ActorSlot_IsLinked(int index);
extern void ApplyRecordTableEntry5(int index, int param2, int param3);
extern void SetShapePosition(CollisionShape *shape, const VecFx32 *position);
extern void OffsetBoxByDelta(const Box *src, Box *dst, const VecFx32 *delta);
extern BOOL func_ov001_0207d484(int enable);

void SetActorRaisedCollision(FieldActor *actor, BOOL raised) {
    VecFx32 arg;
    VecFx32 position;
    CollisionShape *shape;

    if (raised) {
        if (!ActorSlot_IsLinked(actor->slotIndex)) {
            ApplyRecordTableEntry5(actor->slotIndex, 0, 0);
        }
        position.x = actor->position.x;
        position.y = actor->position.y + 0xccd;
        position.z = actor->position.z;
        arg = position;
        shape = &actor->body->shape;
        SetShapePosition(shape, &arg);
        OffsetBoxByDelta(&shape->localBounds, &shape->bounds, &shape->position);
        data_ov001_020a0480->flags |= 0x80000;
        return;
    }
    actor->highlighted = 0;
    func_ov001_0207d484(0);
    data_ov001_020a0480->flags &= ~0x80000;
}
