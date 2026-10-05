#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef struct CollisionShape {
    void *data;
    s32 bounds[6];
    s32 kind;
} CollisionShape;

extern const s16 data_02053580[];
extern void *NNSi_FndAllocFromDefaultHeap(u32 size);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 func_01ffaff4(const VecFx32 *src, VecFx32 *dst);
extern void MTX_RotY33_(MtxFx33 *mtx, fx32 sinVal, fx32 cosVal);
extern CollisionShape InitCylinderShape(void *storage, const VecFx32 *start, const VecFx32 *end, const VecFx32 *axis, fx32 length, fx32 radius);
extern CollisionShape InitCapsuleShape(void *storage, const VecFx32 *start, const VecFx32 *end, const VecFx32 *axis, fx32 length, fx32 radius);
extern CollisionShape func_0203ad28(void *storage, const VecFx32 *center, fx32 radius);
extern CollisionShape InitBoxShape(void *storage, const VecFx32 *center, const VecFx32 *halfExtents, const MtxFx33 *rotation);

static inline void BuildAxialShape0(CollisionShape *shape, void *storage, const VecFx32 *position, const VecFx32 *top, fx32 radius)
{
    VecFx32 axis;
    VecFx32 delta;
    fx32 length;
    VEC_Subtract(top, position, &delta);
    axis = delta;
    length = func_01ffaff4(&axis, &axis);
    *shape = InitCylinderShape(storage, position, top, &axis, length, radius);
}

static inline void BuildAxialShape1(CollisionShape *shape, void *storage, const VecFx32 *position, const VecFx32 *top, fx32 radius)
{
    VecFx32 axis;
    VecFx32 delta;
    fx32 length;
    VEC_Subtract(top, position, &delta);
    axis = delta;
    length = func_01ffaff4(&axis, &axis);
    *shape = InitCapsuleShape(storage, position, top, &axis, length, radius);
}

static inline void BuildSphereShape(CollisionShape *shape, const VecFx32 *position, fx32 radius)
{
    *shape = func_0203ad28(shape->data, position, radius);
}

static inline void BuildBoxShape(CollisionShape *shape, const VecFx32 *position, const VecFx32 *extents, const MtxFx33 *rotation)
{
    *shape = InitBoxShape(shape->data, position, extents, rotation);
}

void BuildCollisionShape(CollisionShape *shape, const VecFx32 *position, int kind, fx32 sizeX, fx32 sizeY, fx32 sizeZ, s32 angle, BOOL allocate)
{
    VecFx32 top;
    VecFx32 capsuleTop;
    VecFx32 extents;
    MtxFx33 rotation;

    switch (kind) {
    case 0: {
        void *storage;

        top = *position;
        top.y += sizeY;
        if (allocate) {
            shape->data = NNSi_FndAllocFromDefaultHeap(0x2c);
        }
        storage = shape->data;
        BuildAxialShape0(shape, storage, position, &top, sizeX);
        return;
    }
    case 1: {
        void *storage;

        capsuleTop = *position;
        capsuleTop.y += sizeY + (sizeX >> 1);
        if (allocate) {
            shape->data = NNSi_FndAllocFromDefaultHeap(0x2c);
        }
        storage = shape->data;
        BuildAxialShape1(shape, storage, position, &capsuleTop, sizeX);
        return;
    }
    case 2:
        if (allocate) {
            shape->data = NNSi_FndAllocFromDefaultHeap(0x10);
        }
        BuildSphereShape(shape, position, sizeX);
        return;
    case 3: {

        extents.x = sizeX;
        extents.y = sizeY;
        extents.z = sizeZ;
        MTX_RotY33_(&rotation, data_02053580[angle >> 4], data_02053580[(0x400 - (angle >> 4)) & 0xfff]);
        if (allocate) {
            shape->data = NNSi_FndAllocFromDefaultHeap(0x40);
        }
        BuildBoxShape(shape, position, &extents, &rotation);
        return;
    }
    default:
        shape->kind = -1;
        return;
    }
}
