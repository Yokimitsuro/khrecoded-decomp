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
extern void func_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 func_01ffaff4(const VecFx32 *src, VecFx32 *dst);
extern CollisionShape InitCylinderShape(void *storage, const VecFx32 *start, const VecFx32 *end, const VecFx32 *axis, fx32 length, fx32 radius);

BOOL InitCylinderCollisionObject(CollisionObject *object, u16 groupMask, s32 ownerId, fx32 radius, fx32 height) {
    VecFx32 top;
    VecFx32 offset;
    VecFx32 axis;
    VecFx32 delta;
    CollisionShape shape;
    void *storage;
    fx32 length;

    InitCollisionObject(object, groupMask, ownerId);
    offset.x = 0;
    offset.y = height;
    offset.z = 0;
    top = offset;
    storage = NNSi_FndAllocFromDefaultHeap(0x2c);
    func_01ff9e3c(&top, &data_0205344c, &delta);
    axis = delta;
    length = func_01ffaff4(&axis, &axis);
    shape = InitCylinderShape(storage, &data_0205344c, &top, &axis, length, radius);
    object->shape = shape;
    return TRUE;
}
