#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct VecFx16 {
    fx16 x;
    fx16 y;
    fx16 z;
} VecFx16;

typedef struct Plane {
    VecFx16 normal;
    u16 pad;
    fx32 dist;
} Plane;

extern void func_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void CrossProductFx32Fx16Out(const VecFx32 *a, const VecFx16 *b, VecFx32 *out);
extern void NormalizeVecFx32ToFx16(const VecFx32 *input, VecFx16 *output);
extern fx32 VEC_DotProductFx16(const VecFx32 *v, const VecFx16 *m);

void ComputeEdgePlane(const VecFx32 *pointA, const VecFx32 *pointB, Plane *plane, const VecFx16 *dir) {
    VecFx32 edge;

    func_01ff9e3c(pointB, pointA, &edge);
    CrossProductFx32Fx16Out(&edge, dir, &edge);
    NormalizeVecFx32ToFx16(&edge, &plane->normal);
    plane->dist = VEC_DotProductFx16(pointA, &plane->normal);
}
