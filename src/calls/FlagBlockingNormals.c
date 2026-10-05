#include "nitro/types.h"
#include "nitro/fx_types.h"

extern void MI_CpuFill8(void *dst, int value, int size);
extern void func_01ff9e3c(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx32 VEC_DotProduct(const VecFx32 *a, const VecFx32 *b);
extern void func_01ff9ea8(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void VEC_Normalize(const VecFx32 *src, VecFx32 *dst);
extern void ScaleVecFx32InPlace(VecFx32 *vec, fx32 scale);
extern void GetUnitCross(VecFx32 *out, const VecFx32 *a, const VecFx32 *b);

static inline s32 Sign(fx32 value)
{
    return value >= 0 ? 1 : -1;
}

BOOL FlagBlockingNormals(const VecFx32 *dir, const VecFx32 *motion, const VecFx32 *normals, const u8 *indices, u8 *hits, int count)
{
    struct {
        VecFx32 scaledSlide;
        VecFx32 unitResult;
        VecFx32 edgeResult;
        VecFx32 normalResult;
        VecFx32 offset;
        VecFx32 scaledSide;
        VecFx32 difference;
        VecFx32 base;
        VecFx32 unit;
        VecFx32 side;
        VecFx32 slide;
        VecFx32 edge;
        VecFx32 normal;
        VecFx32 radial;
        VecFx32 axis;
    } vectors;
    fx32 dot;
    fx32 dirDot;
    fx32 normalDot;
    fx32 motionDot;
    BOOL found;
    int i;
    int j;

    if (count == 0) {
        return FALSE;
    }
    found = FALSE;
    MI_CpuFill8(hits, 0, count);

    for (i = 0; i < count; i++) {
        dot = VEC_DotProduct(&normals[indices[i]], dir);
        if (dot > 2 && dot < 0xffc) {
            GetUnitCross(&vectors.base, &normals[indices[i]], dir);
            vectors.side = vectors.base;
            vectors.axis = vectors.base;
            dot = VEC_DotProduct(motion, &vectors.axis);
            vectors.scaledSide = vectors.side;
            ScaleVecFx32InPlace(&vectors.scaledSide, dot);
            vectors.offset = vectors.scaledSide;
            func_01ff9e3c(motion, &vectors.offset, &vectors.difference);
            vectors.radial = vectors.difference;
            func_01ff9ea8(&vectors.axis, &vectors.radial, &vectors.normalResult);
            vectors.normal = vectors.normalResult;
            dirDot = VEC_DotProduct(&vectors.normal, dir);
            normalDot = VEC_DotProduct(&vectors.normal, &normals[indices[i]]);
            if (Sign(dirDot) == Sign(normalDot) || dirDot == 0 || normalDot == 0) {
                if (dirDot > 0 && normalDot > 0) {
                    hits[i] = TRUE;
                    found = TRUE;
                }
            }
        }
    }

    if (count >= 2) {
        for (i = 0; i < count; i++) {
            if (hits[i]) {
                continue;
            }
            for (j = 0; j < count; j++) {
                if (i != j && VEC_DotProduct(motion, &normals[indices[i]]) < 0
                    && VEC_DotProduct(motion, &normals[indices[j]]) <= 0
                    && VEC_DotProduct(motion, dir) <= 0) {
                    func_01ff9ea8(dir, &normals[indices[j]], &vectors.edgeResult);
                    vectors.edge = vectors.edgeResult;
                    int pairProjection = VEC_DotProduct(&vectors.edge, &normals[indices[i]]);
                    motionDot = -VEC_DotProduct(&vectors.edge, motion);
                    if (Sign(pairProjection) != Sign(motionDot) && pairProjection != 0 && motionDot != 0) {
                        VEC_Normalize(&vectors.edge, &vectors.unitResult);
                        vectors.unit = vectors.unitResult;
                        dot = VEC_DotProduct(motion, &vectors.unit);
                        vectors.scaledSlide = vectors.unit;
                        ScaleVecFx32InPlace(&vectors.scaledSlide, dot);
                        vectors.slide = vectors.scaledSlide;
                        if (VEC_DotProduct(&vectors.slide, &normals[indices[i]]) > 0) {
                            found = TRUE;
                            hits[i] = TRUE;
                            break;
                        }
                    }
                }
            }
        }
    }
    return found;
}
