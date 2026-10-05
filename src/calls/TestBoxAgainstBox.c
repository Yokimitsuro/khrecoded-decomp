#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct CollisionBox {
    VecFx32 center;
    fx32 halfExtents[3];
    VecFx32 axes[3];
} CollisionBox;

typedef struct BoxShapeRef {
    CollisionBox *box;
} BoxShapeRef;

typedef struct PenetrationResult {
    fx32 depth;
    VecFx32 axis;
    s8 axisSign;
    u8 featureId;
    u8 pad_12[2];
} PenetrationResult;

extern PenetrationResult InitMaxDistanceHit(void);
extern VecFx32 SubtractVecFx32Into(const VecFx32 *a, const VecFx32 *b);
extern fx32 GetObbProjectedRadius(const CollisionBox *box, const VecFx32 *axis);
extern BOOL func_0203fbb8(fx32 extent, const VecFx32 *delta, const VecFx32 *axis, u8 featureId, PenetrationResult *result);
extern BOOL func_0204a9f8(const VecFx32 *a, const VecFx32 *b, VecFx32 *cross);
extern void VEC_Normalize(const VecFx32 *src, VecFx32 *dst);
extern fx32 VEC_DotProduct(const VecFx32 *a, const VecFx32 *b);
extern int FX_Mul(int left, int right);
extern int PXI_Init_0203f23c(int value);
extern void WritePenetrationContact(const PenetrationResult *result, void *contact, u32 flags);

BOOL TestBoxAgainstBox(BoxShapeRef *refA, BoxShapeRef *refB, void *contact, u32 flags)
{
    PenetrationResult result = InitMaxDistanceHit();
    VecFx32 delta = SubtractVecFx32Into(&refA->box->center, &refB->box->center);
    CollisionBox *boxes[2];
    VecFx32 axis;
    s8 i;
    s8 j;

    boxes[0] = refA->box;
    boxes[1] = refB->box;
    for (i = 0; i < 2; i++) {
        for (j = 0; j < 3; j++) {
            VecFx32 faceAxis = boxes[i]->axes[j];
            fx32 extent = boxes[i]->halfExtents[j];
            if (!func_0203fbb8(extent + GetObbProjectedRadius(boxes[(s8)(i ^ 1)], &faceAxis), &delta, &faceAxis, 0, &result)) {
                return FALSE;
            }
        }
    }
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            if (!func_0204a9f8(&boxes[0]->axes[i], &boxes[1]->axes[j], &axis)) {
                fx32 extent;
                s8 boxIndex;
                VEC_Normalize(&axis, &axis);
                extent = 0;
                for (boxIndex = 0; boxIndex < 2; boxIndex++) {
                    s8 axisIndex;
                    for (axisIndex = 0; axisIndex < 3; axisIndex++) {
                        if (boxIndex == 0) {
                            if (axisIndex == i) {
                                continue;
                            }
                        } else if (axisIndex == j) {
                            continue;
                        }
                        fx32 dot = VEC_DotProduct(&axis, &boxes[boxIndex]->axes[axisIndex]);
                        extent += PXI_Init_0203f23c(FX_Mul(dot, boxes[boxIndex]->halfExtents[axisIndex]));
                    }
                }
                if (!func_0203fbb8(extent, &delta, &axis, 0, &result)) {
                    return FALSE;
                }
            }
        }
    }
    WritePenetrationContact(&result, contact, flags);
    return TRUE;
}
