#include "libs/nns/g3d/g3d_kernel_internal.h"

void *NNS_G3dGetAnmByIdx(const void *resource, u32 index)
{
    if (resource != NULL) {
        const NNSG3dResFileHeader *header =
            (const NNSG3dResFileHeader *)resource;
        const u32 *blocks =
            (const u32 *)((const u8 *)header + header->headerSize);
        const NNSG3dResAnmSet *animationSet =
            (const NNSG3dResAnmSet *)((const u8 *)header + blocks[0]);
        const NNSG3dResDictAnmSetData *animationData =
            NNS_G3dGetResDataByIdx(&animationSet->dict, index);

        if (animationData != NULL) {
            return (u8 *)animationSet + animationData->offset;
        }
    }

    return NULL;
}
