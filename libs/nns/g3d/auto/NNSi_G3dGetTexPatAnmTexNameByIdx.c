#include "libs/nns/g3d/g3d_kernel_internal.h"

const NNSG3dResName *NNSi_G3dGetTexPatAnmTexNameByIdx(
    const NNSG3dResTexPatAnm *animation,
    u8 textureIndex)
{
    if (animation != NULL && textureIndex < animation->numTex) {
        const NNSG3dResName *names =
            (const NNSG3dResName *)((const u8 *)animation + animation->ofsTexName);

        return &names[textureIndex];
    }

    return NULL;
}
