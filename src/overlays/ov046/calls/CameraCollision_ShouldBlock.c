#include "nitro/types.h"

typedef struct CollisionShape {
    u8 pad_00[0x6c];
    s32 objectType;
} CollisionShape;

typedef struct CollisionObject {
    CollisionShape *shape;
    s32 category;
} CollisionObject;

extern s8 func_ov001_02068084(void);
extern s32 ContainsMatchingEntry(CollisionObject *object, u32 kind);

BOOL CameraCollision_ShouldBlock(CollisionObject *object)
{
    if (func_ov001_02068084() == 5 && object->category == 4 &&
        object->shape->objectType == 0x1e) {
        return TRUE;
    }
    if (ContainsMatchingEntry(object, 4)) {
        return FALSE;
    }
    if (object->category == 4 &&
        (object->shape->objectType == 1 || object->shape->objectType == 0x17)) {
        return FALSE;
    }
    return TRUE;
}
