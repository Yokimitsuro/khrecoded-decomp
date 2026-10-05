#include "libs/nns/g3d/g3d_kernel_internal.h"

const NNSG3dResDictTexPatAnmData *NNSi_G3dGetTexPatAnmDataByIdx(
    const NNSG3dResTexPatAnm *animation,
    u32 index)
{
    return (const NNSG3dResDictTexPatAnmData *)
        NNS_G3dGetResDataByIdx(&animation->dict, index);
}
