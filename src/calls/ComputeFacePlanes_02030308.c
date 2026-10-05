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

extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void func_01ff9ea8(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void VEC_Normalize(const VecFx32 *in, VecFx32 *out);
extern void NormalizeVecFx32ToFx16(const VecFx32 *input, VecFx16 *output);
extern fx32 VEC_DotProductFx16(const VecFx32 *v, const VecFx16 *m);
extern void ComputeEdgePlane(const VecFx32 *pointA, const VecFx32 *pointB, Plane *plane, const VecFx16 *dir);

/* Computes a face's normal plane and edge planes. */
void ComputeFacePlanes_02030308(void *unused, u8 *face)
{
    VecFx32 *vertexBase = (VecFx32 *)(face + 0x50);
    Plane *edgeBase = (Plane *)(face + 0x20);
    VecFx32 edge1;
    VecFx32 edge2;
    VecFx32 crossNormal;

    VEC_Subtract((VecFx32 *)((u8 *)vertexBase + 0xc), vertexBase, &edge1);
    VEC_Subtract((VecFx32 *)((u8 *)vertexBase + 0x18), vertexBase, &edge2);
    func_01ff9ea8(&edge1, &edge2, &crossNormal);
    VEC_Normalize(&crossNormal, &crossNormal);
    NormalizeVecFx32ToFx16(&crossNormal, (VecFx16 *)(face + 0x14));
    *(fx32 *)(face + 0x1c) = VEC_DotProductFx16(vertexBase, (VecFx16 *)(face + 0x14));
    if ((*(fx16 *)(face + 0x14) | *(fx16 *)(face + 0x18)) == 0) {
        *(u16 *)(face + 0x10) = *(u16 *)(face + 0x10) | 2;
    }
    ComputeEdgePlane(vertexBase, (VecFx32 *)((u8 *)vertexBase + 0xc), edgeBase, (VecFx16 *)(face + 0x14));
    ComputeEdgePlane((VecFx32 *)((u8 *)vertexBase + 0xc), (VecFx32 *)((u8 *)vertexBase + 0x18),
                  (Plane *)((u8 *)edgeBase + 0xc), (VecFx16 *)(face + 0x14));
    if (*(u16 *)(face + 0x12) == 3) {
        ComputeEdgePlane((VecFx32 *)((u8 *)vertexBase + 0x18), vertexBase, (Plane *)((u8 *)edgeBase + 0x18),
                      (VecFx16 *)(face + 0x14));
        return;
    }
    ComputeEdgePlane((VecFx32 *)((u8 *)vertexBase + 0x18), (VecFx32 *)((u8 *)vertexBase + 0x24),
                  (Plane *)((u8 *)edgeBase + 0x18), (VecFx16 *)(face + 0x14));
    ComputeEdgePlane((VecFx32 *)((u8 *)vertexBase + 0x24), vertexBase, (Plane *)((u8 *)edgeBase + 0x24),
                  (VecFx16 *)(face + 0x14));
}
