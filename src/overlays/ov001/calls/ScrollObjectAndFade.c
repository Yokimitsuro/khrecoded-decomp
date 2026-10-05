#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ActorNode {
    u8 pad_000[0x10c];
    u8 collision[0x130 - 0x10c];
    u8 shape[4];
} ActorNode;

typedef struct ScrollingObject {
    u8 pad_00[0x38];
    u8 actorId;
    u8 pad_39[7];
    VecFx32 position;
    u8 pad_4c[0xc];
    u32 colorBits : 27;
    u32 alpha : 5;
    u8 pad_5c[0x18];
    int track;
} ScrollingObject;

extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern ActorNode *ActorRegistry_GetEntityByIndex(u16 actorId);
extern void SetShapePosition(void *shape, const VecFx32 *position);
extern void SetCollisionObjectPosition(void *object, const VecFx32 *position);
extern void FieldObject_SetPhaseMode(ScrollingObject *object, int mode);
extern unsigned int IsOffsetBeyondActiveRecord(int firstOffset, int secondOffset);
extern void UnlinkPendingNode(int track);
extern int func_ov031_020bc720(void);

static inline VecFx32 MakeVec(fx32 x, fx32 y, fx32 z)
{
    VecFx32 v;
    v.x = x;
    v.y = y;
    v.z = z;
    return v;
}

static inline VecFx32 AddVec(const VecFx32 *a, const VecFx32 *b)
{
    VecFx32 sum;
    VEC_Add(a, b, &sum);
    return sum;
}

int ScrollObjectAndFade(ScrollingObject *object, VecFx32 *delta)
{
    ActorNode *actor = ActorRegistry_GetEntityByIndex(object->actorId);
    VecFx32 center;
    VecFx32 offset;
    int depth;

    VEC_Add(&object->position, delta, &object->position);
    SetShapePosition(actor->shape, &object->position);
    offset = MakeVec(0, 0xa66, 0);
    center = AddVec(&object->position, &offset);
    SetCollisionObjectPosition(actor->collision, &center);
    if (IsOffsetBeyondActiveRecord(object->position.z, 0x59a)) {
        UnlinkPendingNode(object->track);
        FieldObject_SetPhaseMode(object, 2);
    }
    depth = object->position.z + 0x59a + func_ov031_020bc720();
    if (depth < 0x10) {
        object->alpha = 0;
    } else if (depth < 0x1800) {
        object->alpha = depth * 31 / 0x1800;
    } else {
        object->alpha = 31;
    }
    return 0;
}
