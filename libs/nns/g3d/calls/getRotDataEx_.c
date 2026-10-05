#include "libs/nns/g3d/g3d_nsbca_internal.h"

typedef enum NNSG3dJntAnmRInfo_ {
    NNS_G3D_JNTANM_RINFO_STEP_1 = 0x00000000,
    NNS_G3D_JNTANM_RINFO_STEP_2 = 0x40000000,
    NNS_G3D_JNTANM_RINFO_STEP_4 = 0x80000000,
    NNS_G3D_JNTANM_RINFO_LAST_INTERP_MASK = 0x1fff0000,
    NNS_G3D_JNTANM_RINFO_STEP_MASK = 0xc0000000,
    NNS_G3D_JNTANM_RINFO_LAST_INTERP_SHIFT = 16
} NNSG3dJntAnmRInfo;

#define NNS_G3D_JNTANM_OPTION_END_TO_START_INTERPOLATION 0x02
#define ROT_FILTER_SHIFT 0

extern BOOL getRotDataByIdx_(MtxFx33 *rotation, const void *rot3,
                             const void *rot5, u32 info);
extern void VEC_Normalize(const VecFx32 *source, VecFx32 *destination);

static inline void vecCross_(const VecFx32 *a, const VecFx32 *b, VecFx32 *result)
{
    fx32 x, y, z;

    x = (a->y * b->z - a->z * b->y) >> FX32_SHIFT;
    y = (a->z * b->x - a->x * b->z) >> FX32_SHIFT;
    z = (a->x * b->y - a->y * b->x) >> FX32_SHIFT;
    result->x = x;
    result->y = y;
    result->z = z;
}

void getRotDataEx_(MtxFx33 *rotation, fx32 frameValue, const u32 *data,
                   const NNSG3dResJntAnm *animation)
{
    const void *array = (const u8 *)animation + data[1];
    const void *rot3 = (const u8 *)animation + animation->ofsRot3;
    const void *rot5 = (const u8 *)animation + animation->ofsRot5;
    NNSG3dJntAnmRInfo info = (NNSG3dJntAnmRInfo)data[0];
    u32 lastInterpolation;
    u32 index0, index1;
    fx32 remainder;
    int step;
    u32 stepShift;
    u32 frame;
    const u16 *indices = array;

    frame = (u32)(frameValue >> FX32_SHIFT);

    if (frame == animation->numFrame - 1) {
        if (!(info & NNS_G3D_JNTANM_RINFO_STEP_MASK)) {
            index0 = frame;
        } else if (info & NNS_G3D_JNTANM_RINFO_STEP_2) {
            index0 = (frame >> 1) + (frame & 1);
        } else {
            index0 = (frame >> 2) + (frame & 3);
        }

        if (animation->flag & NNS_G3D_JNTANM_OPTION_END_TO_START_INTERPOLATION) {
            index1 = 0;
            goto interpolatePair;
        } else {
            if (getRotDataByIdx_(rotation, rot3, rot5, indices[index0])) {
                vecCross_((const VecFx32 *)&rotation->_00,
                          (const VecFx32 *)&rotation->_10,
                          (VecFx32 *)&rotation->_20);
            } else {
                VEC_Normalize((VecFx32 *)&rotation->_20,
                              (VecFx32 *)&rotation->_20);
            }
            return;
        }
    }

    if (!(info & NNS_G3D_JNTANM_RINFO_STEP_MASK)) {
        goto interpolateNextFrame;
    }

    lastInterpolation = ((u32)info & NNS_G3D_JNTANM_RINFO_LAST_INTERP_MASK) >>
                        NNS_G3D_JNTANM_RINFO_LAST_INTERP_SHIFT;

    if (info & NNS_G3D_JNTANM_RINFO_STEP_2) {
        if (frame >= lastInterpolation) {
            index0 = lastInterpolation >> 1;
            index1 = index0 + 1;
            goto interpolatePair;
        } else {
            index0 = frame >> 1;
            index1 = index0 + 1;
            remainder = frameValue & (FX32_ONE * 2 - 1);
            step = 2;
            stepShift = 1;
            goto interpolate;
        }
    } else {
        if (frame >= lastInterpolation) {
            index0 = (frame >> 2) + (frame & 3);
            index1 = index0 + 1;
            goto interpolatePair;
        } else {
            index0 = frame >> 2;
            index1 = index0 + 1;
            remainder = frameValue & (FX32_ONE * 4 - 1);
            step = 4;
            stepShift = 2;
            goto interpolate;
        }
    }

interpolateNextFrame:
    index0 = frame;
    index1 = index0 + 1;
interpolatePair:
    remainder = frameValue & (FX32_ONE - 1);
    step = 1;
    stepShift = 0;
interpolate:
    {
        MtxFx33 first, second;
        BOOL reconstructThirdRow = FALSE;

        reconstructThirdRow |= getRotDataByIdx_(&first, rot3, rot5, indices[index0]);
        reconstructThirdRow |= getRotDataByIdx_(&second, rot3, rot5, indices[index1]);

        rotation->_00 = ((first._00 * step) + (((second._00 - first._00) * remainder) >> FX32_SHIFT)) >> (stepShift * ROT_FILTER_SHIFT);
        rotation->_01 = ((first._01 * step) + (((second._01 - first._01) * remainder) >> FX32_SHIFT)) >> (stepShift * ROT_FILTER_SHIFT);
        rotation->_02 = ((first._02 * step) + (((second._02 - first._02) * remainder) >> FX32_SHIFT)) >> (stepShift * ROT_FILTER_SHIFT);
        rotation->_10 = ((first._10 * step) + (((second._10 - first._10) * remainder) >> FX32_SHIFT)) >> (stepShift * ROT_FILTER_SHIFT);
        rotation->_11 = ((first._11 * step) + (((second._11 - first._11) * remainder) >> FX32_SHIFT)) >> (stepShift * ROT_FILTER_SHIFT);
        rotation->_12 = ((first._12 * step) + (((second._12 - first._12) * remainder) >> FX32_SHIFT)) >> (stepShift * ROT_FILTER_SHIFT);

        VEC_Normalize((VecFx32 *)&rotation->_00, (VecFx32 *)&rotation->_00);
        VEC_Normalize((VecFx32 *)&rotation->_10, (VecFx32 *)&rotation->_10);

        if (!reconstructThirdRow) {
            rotation->_20 = ((first._20 * step) + (((second._20 - first._20) * remainder) >> FX32_SHIFT)) >> (stepShift * ROT_FILTER_SHIFT);
            rotation->_21 = ((first._21 * step) + (((second._21 - first._21) * remainder) >> FX32_SHIFT)) >> (stepShift * ROT_FILTER_SHIFT);
            rotation->_22 = ((first._22 * step) + (((second._22 - first._22) * remainder) >> FX32_SHIFT)) >> (stepShift * ROT_FILTER_SHIFT);
            VEC_Normalize((VecFx32 *)&rotation->_20, (VecFx32 *)&rotation->_20);
        } else {
            vecCross_((const VecFx32 *)&rotation->_00,
                      (const VecFx32 *)&rotation->_10,
                      (VecFx32 *)&rotation->_20);
        }
        return;
    }
}
