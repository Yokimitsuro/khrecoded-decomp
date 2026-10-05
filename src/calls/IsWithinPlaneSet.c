#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ShapeData {
    VecFx32 center;
    VecFx32 halfExtent;
    u8 pad_18[0x24];
    u8 isOriented : 1;
} ShapeData;

typedef struct CollisionShape {
    ShapeData *data;
    s32 bounds[6];
    s32 kind;
} CollisionShape;

extern VecFx32 *func_ov021_020af5d4(void);
extern VecFx32 *func_ov021_020af71c(void);
extern VecFx32 GetShapeCenter(const CollisionShape *shape);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 VEC_DotProduct(const VecFx32 *a, const VecFx32 *b);
extern int MSL_AbsA(int value);
extern void ApplyScalarToVec3(VecFx32 *vec, int (*transform)(int));
extern fx32 GetShapeProjectedRadius(const CollisionShape *shape, const VecFx32 *normal);

static inline VecFx32 SubtractVec(const VecFx32 *a, const VecFx32 *b)
{
    VecFx32 result;
    VEC_Subtract(a, b, &result);
    return result;
}

static inline VecFx32 AbsVec(VecFx32 vec)
{
    ApplyScalarToVec3(&vec, MSL_AbsA);
    return vec;
}

BOOL IsWithinPlaneSet(const CollisionShape *shape, fx32 margin)
{
    VecFx32 *origin = func_ov021_020af5d4();
    VecFx32 relative;
    VecFx32 center = GetShapeCenter(shape);
    VecFx32 *normals;
    u8 i;

    relative = SubtractVec(&center, origin);
    normals = func_ov021_020af71c();
    if (shape->kind == 1 && shape->data->isOriented) {
        for (i = 0; i < 4; i++) {
            VecFx32 absNormal = AbsVec(normals[i]);
            fx32 radius = VEC_DotProduct(&absNormal, &shape->data->halfExtent);
            if (VEC_DotProduct(&normals[i], &relative) > radius + margin) {
                return FALSE;
            }
        }
    } else {
        for (i = 0; i < 4; i++) {
            fx32 radius = GetShapeProjectedRadius(shape, &normals[i]);
            if (VEC_DotProduct(&normals[i], &relative) > radius + margin) {
                return FALSE;
            }
        }
    }
    return TRUE;
}
