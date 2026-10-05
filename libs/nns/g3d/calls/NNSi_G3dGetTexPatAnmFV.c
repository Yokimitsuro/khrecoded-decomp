#include "libs/nns/g3d/g3d_kernel_internal.h"

extern const NNSG3dResDictTexPatAnmData *NNSi_G3dGetTexPatAnmDataByIdx(
    const NNSG3dResTexPatAnm *animation,
    u32 index);

const NNSG3dResTexPatAnmFV *NNSi_G3dGetTexPatAnmFV(
    const NNSG3dResTexPatAnm *animation,
    u32 index,
    u32 frame)
{
    const NNSG3dResDictTexPatAnmData *animationData =
        NNSi_G3dGetTexPatAnmDataByIdx(animation, index);
    const NNSG3dResTexPatAnmFV *frameValues =
        (const NNSG3dResTexPatAnmFV *)
        ((const u8 *)animation + animationData->offset);
    const u32 estimatedIndex =
        (u32)((fx32)animationData->ratioDataFrame * frame >> FX32_SHIFT);
    u32 frameValueIndex = estimatedIndex;

    while (frameValueIndex > 0 &&
           frameValues[frameValueIndex].idxFrame >= frame) {
        frameValueIndex--;
    }

    while (frameValueIndex + 1 < animationData->numFV &&
           frameValues[frameValueIndex + 1].idxFrame <= frame) {
        frameValueIndex++;
    }

    return &frameValues[frameValueIndex];
}
