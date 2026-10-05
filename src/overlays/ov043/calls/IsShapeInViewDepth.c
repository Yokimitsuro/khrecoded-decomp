#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CollisionShape CollisionShape;

extern VecFx32 GetShapeCenter(const CollisionShape *shape);
extern fx32 GetShapeProjectedRadius(const CollisionShape *shape, const VecFx32 *axis);
extern s32 func_ov031_020bc720(void);
extern BOOL IsWithinPlaneSet(const CollisionShape *shape, s32 margin);

static inline VecFx32 MakeVec(fx32 x, fx32 y, fx32 z) {
    VecFx32 out;
    out.x = x;
    out.y = y;
    out.z = z;
    return out;
}

BOOL IsShapeInViewDepth(const CollisionShape *shape, s32 margin) {
    VecFx32 center = GetShapeCenter(shape);
    BOOL result = FALSE;
    VecFx32 axis = MakeVec(0, 0, 0x1000);
    s32 depth = func_ov031_020bc720();
    if (center.z >= -(margin + (depth + GetShapeProjectedRadius(shape, &axis)))) {
        result = IsWithinPlaneSet(shape, margin);
    }
    return result;
}
