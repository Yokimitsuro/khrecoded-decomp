#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef struct Plane {
    VecFx16 normal;
    u16 pad;
    fx32 dist;
} Plane;

typedef struct Face {
    u8 pad_00[0x12];
    u16 vertexCount;
    Plane facePlane;
    Plane edgePlanes[4];
    VecFx32 vertices[4];
} Face;

extern void func_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void func_01ff9ea8(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void VEC_Normalize(VecFx32 *in, VecFx32 *out);
extern void NormalizeVecFx32ToFx16(const VecFx32 *input, VecFx16 *output);
extern fx32 VEC_DotProductFx16(const VecFx32 *v, const VecFx16 *m);
extern void ComputeEdgePlane(const VecFx32 *pointA, const VecFx32 *pointB, Plane *plane, const VecFx16 *dir);

void ComputeFacePlanes(void *unused, Face *face)
{
    VecFx32 *v0 = &face->vertices[0];
    Plane *edgePlane = &face->edgePlanes[0];
    VecFx16 *normal;
    VecFx32 edge1;
    VecFx32 edge2;
    VecFx32 rawNormal;

    func_01ff9e3c(v0 + 1, v0, &edge1);
    func_01ff9e3c(v0 + 2, v0, &edge2);
    func_01ff9ea8(&edge1, &edge2, &rawNormal);
    VEC_Normalize(&rawNormal, &rawNormal);
    NormalizeVecFx32ToFx16(&rawNormal, &face->facePlane.normal);
    face->facePlane.dist = VEC_DotProductFx16(v0, &face->facePlane.normal);

    normal = &face->facePlane.normal;
    ComputeEdgePlane(v0, v0 + 1, edgePlane, normal);
    ComputeEdgePlane(v0 + 1, v0 + 2, edgePlane + 1, normal);

    if (face->vertexCount == 3) {
        ComputeEdgePlane(v0 + 2, v0, edgePlane + 2, normal);
        return;
    }
    ComputeEdgePlane(v0 + 2, v0 + 3, edgePlane + 2, normal);
    ComputeEdgePlane(v0 + 3, v0, edgePlane + 3, normal);
}
