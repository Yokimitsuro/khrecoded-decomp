#include "libs/nns/g3d/g3d_kernel_internal.h"

const NNSG3dResName *NNSi_G3dGetTexPatAnmPlttNameByIdx(
    const NNSG3dResTexPatAnm *animation,
    u8 paletteIndex)
{
    if (animation != NULL && paletteIndex < animation->numPltt) {
        const NNSG3dResName *names =
            (const NNSG3dResName *)((const u8 *)animation + animation->ofsPlttName);

        return &names[paletteIndex];
    }

    return NULL;
}
