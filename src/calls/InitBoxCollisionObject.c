#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

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

extern const s16 data_02053580[];
extern BOOL InitCollisionObject(CollisionObject *object, u16 groupMask, s32 ownerId);
extern void *NNSi_FndAllocFromDefaultHeap(u32 size);
extern void MTX_RotY33_(MtxFx33 *mtx, fx32 sinVal, fx32 cosVal);
extern CollisionShape InitBoxShape(void *storage, const VecFx32 *center, const VecFx32 *halfExtents, const MtxFx33 *rotation);

BOOL InitBoxCollisionObject(CollisionObject *object, u16 groupMask, s32 ownerId, fx32 sizeX, fx32 sizeY, fx32 sizeZ, s32 angle) {
    MtxFx33 rotation;
    VecFx32 center;
    VecFx32 halfExtents;
    VecFx32 centerInit;
    VecFx32 halfInit;
    CollisionShape shape;
    int angleIndex;

    InitCollisionObject(object, groupMask, ownerId);
    angleIndex = angle >> 4;
    MTX_RotY33_(&rotation, data_02053580[angleIndex], data_02053580[(0x400 - angleIndex) & 0xfff]);
    halfInit.x = sizeX / 2;
    halfInit.y = sizeY / 2;
    halfInit.z = sizeZ / 2;
    halfExtents = halfInit;
    centerInit.x = 0;
    centerInit.y = halfInit.y;
    centerInit.z = 0;
    center = centerInit;
    shape = InitBoxShape(NNSi_FndAllocFromDefaultHeap(0x40), &center, &halfExtents, &rotation);
    object->shape = shape;
    return TRUE;
}
