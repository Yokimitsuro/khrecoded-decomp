#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ShapeData {
    VecFx32 center;
    VecFx32 halfExtent;
    VecFx32 axes[3];
    u8 flags;
} ShapeData;

typedef struct CollisionShape {
    ShapeData *data;
} CollisionShape;

typedef struct ShapeBounds {
    VecFx32 max;
    VecFx32 min;
} ShapeBounds;

extern int MSL_AbsD(int value);
extern void ApplyScalarToVec3(VecFx32 *vec, int (*transform)(int));
extern void ScaleVecFx32InPlace(VecFx32 *vec, fx32 scale);
extern void NegateVecFx32(VecFx32 *vec);
extern void func_01ff9e0c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);

static inline VecFx32 AbsVec(VecFx32 vec)
{
    ApplyScalarToVec3(&vec, MSL_AbsD);
    return vec;
}

static inline VecFx32 ScaledVec(VecFx32 vec, fx32 scale)
{
    ScaleVecFx32InPlace(&vec, scale);
    return vec;
}

static inline VecFx32 NegatedVec(VecFx32 vec)
{
    NegateVecFx32(&vec);
    return vec;
}

void GetShapeBounds(const CollisionShape *shape, ShapeBounds *bounds)
{
    ShapeData *data = shape->data;
    VecFx32 extentY;
    VecFx32 extentZ;

    if (data->flags & 1) {
        bounds->max = data->halfExtent;
    } else {
        bounds->max = ScaledVec(AbsVec(data->axes[0]), data->halfExtent.x);
        extentY = ScaledVec(AbsVec(data->axes[1]), data->halfExtent.y);
        func_01ff9e0c(&bounds->max, &extentY, &bounds->max);
        extentZ = ScaledVec(AbsVec(data->axes[2]), data->halfExtent.z);
        func_01ff9e0c(&bounds->max, &extentZ, &bounds->max);
    }
    bounds->min = NegatedVec(bounds->max);
    func_01ff9e0c(&bounds->max, &data->center, &bounds->max);
    func_01ff9e0c(&bounds->min, &data->center, &bounds->min);
}
