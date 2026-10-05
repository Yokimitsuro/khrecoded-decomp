#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CollisionShape {
    void *data;
    s32 bounds[6];
    s32 kind;
} CollisionShape;

typedef struct CollisionObject {
    u8 pad_00[0x24];
    CollisionShape shape;
    u8 pad_44[0x44];
} CollisionObject;

extern const VecFx32 data_0205344c;
extern BOOL InitCollisionObject(CollisionObject *object, u16 groupMask, s32 ownerId);
extern void *NNSi_FndAllocFromDefaultHeap(u32 size);
extern CollisionShape func_0203ad28(void *storage, const VecFx32 *center, fx32 radius);

BOOL InitSphereCollisionObject(CollisionObject *object, u16 groupMask, s32 ownerId, fx32 radius) {
    InitCollisionObject(object, groupMask, ownerId);
    object->shape = func_0203ad28(NNSi_FndAllocFromDefaultHeap(0x10), &data_0205344c, radius);
    return TRUE;
}
