#define G3D_KERNEL_CUSTOM_RESOURCE_INLINE
#include "libs/nns/g3d/g3d_kernel_internal.h"

inline u32 NNS_GfdGetTexKeyAddr(u32 key)
{
    return (u32)((key & 0x0000ffff) << NNS_GFD_TEXKEY_ADDR_SHIFT);
}

inline void *NNS_G3dGetResDataByIdx(
    const NNSG3dResDict *dict,
    u32 index)
{
    NNSG3dResDictEntryHeader *header;

    if (dict != NULL && index < dict->numEntry) {
        header = (NNSG3dResDictEntryHeader *)((u8 *)dict + dict->ofsEntry);
        return &header->data[0] + header->sizeUnit * index;
    }
    return NULL;
}

inline NNSG3dResMatData *NNS_G3dGetMatDataByIdx(
    const NNSG3dResMat *mat,
    u32 index)
{
    NNSG3dResDictMatData *data;

    if (mat) {
        data = NNS_G3dGetResDataByIdx(&mat->dict, index);
        if (data) {
            return (NNSG3dResMatData *)((u8 *)mat + data->offset);
        }
    }
    return NULL;
}

void bindMdlPltt_Internal_(
    NNSG3dResMat *mat,
    NNSG3dResDictPlttToMatIdxData *binding,
    const NNSG3dResTex *tex,
    const NNSG3dResDictPlttData *paletteData)
{
    u8 *indices = (u8 *)mat + binding->offset;
    u16 paletteBase = paletteData->offset;
    u16 vramOffset =
        (u16)(NNS_GfdGetTexKeyAddr(tex->plttInfo.vramKey) >>
              NNS_GFD_TEXKEY_ADDR_SHIFT);
    u32 i;

    if (!(paletteData->flag & 1)) {
        paletteBase >>= 1;
        vramOffset >>= 1;
    }

    for (i = 0; i < binding->numIdx; ++i) {
        NNSG3dResMatData *material =
            NNS_G3dGetMatDataByIdx(mat, indices[i]);
        material->texPlttBase = (u16)(paletteBase + vramOffset);
    }

    binding->flag |= 1;
}
