#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef struct CollisionSphere {
    VecFx32 center;
    fx32 radius;
} CollisionSphere;

typedef struct OrientedBox {
    VecFx32 center;
    VecFx32 halfExtents;
    MtxFx33 axes;
} OrientedBox;

typedef struct SphereContact {
    fx32 depth;
    VecFx32 normal;
    s32 time;
    u8 onEdge;
} SphereContact;

extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 FX_Sqrt(fx32 value);
extern void MTX_MultVec33(const VecFx32 *vec, const MtxFx33 *m, VecFx32 *dst);
extern fx32 PXI_Init_0203f23c(fx32 value);
extern s32 Sign(s32 value);
extern fx32 Vec_DotSelf(const VecFx32 *v);
extern fx32 SquareFx32ToFx64(fx32 value);
extern s32 SignNonNegativeOne(s32 value);
extern VecFx32 VecFx32DividedByScalar(const VecFx32 *vec, fx32 divisor);
extern void NegateVecFx32(VecFx32 *vec);
extern void TransformVectorByBasis(const VecFx32 *vec, const MtxFx33 *basis, VecFx32 *out);

BOOL TestSphereAgainstBox(CollisionSphere **sphereRef, OrientedBox **boxRef, SphereContact *contact, u32 flags)
{
    CollisionSphere *sphere = *sphereRef;
    OrientedBox *box = *boxRef;
    VecFx32 local;
    VecFx32 excess;
    fx32 distSq;
    fx32 absX;
    fx32 absY;
    fx32 absZ;
    BOOL onEdge;

    VEC_Subtract(&sphere->center, &box->center, &local);
    TransformVectorByBasis(&local, &box->axes, &local);
    if (PXI_Init_0203f23c(local.x) > box->halfExtents.x) {
        excess.x = local.x - box->halfExtents.x * Sign(local.x);
    } else {
        excess.x = 0;
    }
    if (PXI_Init_0203f23c(local.y) > box->halfExtents.y) {
        excess.y = local.y - box->halfExtents.y * Sign(local.y);
    } else {
        excess.y = 0;
    }
    if (PXI_Init_0203f23c(local.z) > box->halfExtents.z) {
        excess.z = local.z - box->halfExtents.z * Sign(local.z);
    } else {
        excess.z = 0;
    }
    distSq = Vec_DotSelf(&excess);
    if (distSq > SquareFx32ToFx64(sphere->radius)) {
        return FALSE;
    }
    if (contact != NULL) {
        if (distSq == 0) {
            absX = PXI_Init_0203f23c(local.x);
            absY = PXI_Init_0203f23c(local.y);
            absZ = PXI_Init_0203f23c(local.z);
            if (absX > absY) {
                if (absX > absZ) {
                    contact->depth = sphere->radius + box->halfExtents.x - absX;
                    excess.x = SignNonNegativeOne(local.x) << 12;
                } else {
                    contact->depth = sphere->radius + box->halfExtents.z - absZ;
                    excess.z = SignNonNegativeOne(local.z) << 12;
                }
            } else if (absY > absZ) {
                contact->depth = sphere->radius + box->halfExtents.y - absY;
                excess.y = SignNonNegativeOne(local.y) << 12;
            } else {
                contact->depth = sphere->radius + box->halfExtents.z - absZ;
                excess.z = SignNonNegativeOne(local.z) << 12;
            }
            contact->normal = excess;
            onEdge = FALSE;
        } else {
            fx32 length = FX_Sqrt(distSq);
            contact->depth = sphere->radius - length;
            contact->normal = VecFx32DividedByScalar(&excess, length);
            onEdge = (excess.x != 0) + (excess.y != 0) + (excess.z != 0) >= 2;
        }
        contact->onEdge = onEdge;
        if (flags & 1) {
            NegateVecFx32(&contact->normal);
        }
        MTX_MultVec33(&contact->normal, &box->axes, &contact->normal);
    }
    return TRUE;
}
