#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "nitro/fx.h"

typedef struct ContactEntry {
    void *object;
    s32 type;
    u8 flags;
} ContactEntry;

typedef struct ContactSet {
    ContactEntry entries[16];
    VecFx32 normals[16];
    u8 entryCount;
} ContactSet;

extern void GetNormalizedAxisRejectionMasked(VecFx32 *out, const VecFx32 *v, const VecFx32 *normal, BOOL normalize);
extern fx32 VEC_DotProduct(const VecFx32 *a, const VecFx32 *b);
extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 ComputeOneMinusSquareFraction(fx32 value);
extern void NegateVecFx32(VecFx32 *vec);
extern s64 _ll_mul(s64 a, s64 b);

static inline VecFx32 VecMake(fx32 x, fx32 y, fx32 z)
{
    VecFx32 v;
    v.x = x;
    v.y = y;
    v.z = z;
    return v;
}

static inline VecFx32 VecSum(const VecFx32 *a, const VecFx32 *b)
{
    VecFx32 sum;
    VEC_Add(a, b, &sum);
    return sum;
}

static inline VecFx32 CrossWithVertical(const VecFx32 *v, const VecFx32 *axis)
{
    VecFx32 cross;
    cross.x = -(fx32)((_ll_mul(v->z, axis->y) + 0x800) >> 12);
    cross.y = 0;
    cross.z = (fx32)((_ll_mul(v->x, axis->y) + 0x800) >> 12);
    return cross;
}

static inline void ProjectHorizontal(VecFx32 *out, const VecFx32 *v)
{
    VecFx32 up = VecMake(0, FX32_ONE, 0);
    GetNormalizedAxisRejectionMasked(out, v, &up, TRUE);
}

static inline VecFx32 HorizontalDirection(const VecFx32 *v)
{
    VecFx32 up = VecMake(0, FX32_ONE, 0);
    VecFx32 direction;
    GetNormalizedAxisRejectionMasked(&direction, v, &up, TRUE);
    return direction;
}

static inline VecFx32 RotateAboutVertical(const VecFx32 *v, fx32 sign)
{
    VecFx32 axis = VecMake(0, sign, 0);
    return CrossWithVertical(v, &axis);
}

static inline VecFx32 RotatedSum(const VecFx32 *a, const VecFx32 *b)
{
    VecFx32 axis;
    VecFx32 sum;
    return CrossWithVertical((sum = VecSum(a, b), &sum), (axis = VecMake(0, FX32_ONE, 0), &axis));
}

BOOL AreWallNormalsEnclosing(ContactSet *contacts, fx32 margin)
{
    VecFx32 edges[2];
    VecFx32 bisector;
    VecFx32 direction;
    int count;
    int start;
    int contactIndex;
    int flipIndex;
    int checkIndex;

    count = contacts->entryCount;
    if (count >= 2) {
        for (start = 0;; start++) {
            if (contacts->entries[start].type != 0) {
                break;
            }
            if (start >= count - 2) {
                return FALSE;
            }
        }
        for (checkIndex = start; checkIndex < count; checkIndex++) {
            if (contacts->normals[checkIndex].x == 0 && contacts->normals[checkIndex].z == 0) {
                return FALSE;
            }
        }
        ProjectHorizontal(&edges[0], &contacts->normals[start]);
        edges[1] = HorizontalDirection(&contacts->normals[start + 1]);
        flipIndex = 1;
        if (VEC_DotProduct(&edges[0], &edges[1]) < -ComputeOneMinusSquareFraction(margin)) {
            return TRUE;
        }
        edges[0] = RotateAboutVertical(&edges[0], FX32_ONE);
        edges[1] = RotateAboutVertical(&edges[1], FX32_ONE);
        bisector = RotatedSum(&edges[0], &edges[1]);
        if (VEC_DotProduct(&bisector, &edges[0]) > 0) {
            flipIndex = 0;
        }
        NegateVecFx32(&edges[flipIndex]);
        for (contactIndex = start + 2; contactIndex < count; contactIndex++) {
            fx32 dot0;
            fx32 dot1;
            int edgeIndex;
            direction = HorizontalDirection(&contacts->normals[contactIndex]);
            dot0 = VEC_DotProduct(&edges[0], &direction);
            dot1 = VEC_DotProduct(&edges[1], &direction);
            if (dot0 < margin && dot1 < margin) {
                return TRUE;
            }
            if (dot0 <= 0 || dot1 <= 0) {
                edgeIndex = dot0 >= 0;
                edges[edgeIndex] = RotateAboutVertical(&direction, edgeIndex != flipIndex ? FX32_ONE : -FX32_ONE);
            }
        }
    }
    return FALSE;
}
