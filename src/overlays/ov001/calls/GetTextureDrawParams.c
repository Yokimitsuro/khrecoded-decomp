#include "nitro/types.h"
#include "nnsys/g3d.h"

typedef struct TextureDrawParams {
    u16 width;
    u16 height;
    u32 imageParam;
    u32 paletteBase;
} TextureDrawParams;

extern NNSG3dResTex *NNS_G3dGetTex(const NNSG3dResFileHeader *header);

static inline void *GetDictData(const NNSG3dResDict *dict, u32 index)
{
    const NNSG3dResDictEntryHeader *entries;

    if (dict != NULL && index < dict->numEntry) {
        entries = (const NNSG3dResDictEntryHeader *)((u8 *)dict + dict->ofsEntry);
        return (void *)((u8 *)entries->data + entries->sizeUnit * index);
    }
    return NULL;
}

void GetTextureDrawParams(TextureDrawParams *params, const NNSG3dResFileHeader *file, u32 texIndex)
{
    NNSG3dResTex *tex;
    const NNSG3dResDictTexData *texData;
    const NNSG3dResDictPlttData *plttData;
    u16 plttOffset;
    u16 plttKey;
    u16 texKey;

    tex = NNS_G3dGetTex(file);
    if (tex != NULL) {
        texData = GetDictData(&tex->dict, texIndex);
    } else {
        texData = NULL;
    }
    if (tex != NULL && tex->plttInfo.ofsDict != 0) {
        plttData = GetDictData((const NNSG3dResDict *)((u8 *)tex + tex->plttInfo.ofsDict), 0);
    } else {
        plttData = NULL;
    }

    plttOffset = plttData->offset;
    plttKey = tex->plttInfo.vramKey;
    if ((u8)((texData->texImageParam & 0x1c000000) >> 26) == 5) {
        texKey = tex->tex4x4Info.vramKey;
    } else {
        texKey = tex->texInfo.vramKey;
    }
    if ((plttData->flag & 1) == 0) {
        plttOffset >>= 1;
        plttKey >>= 1;
    }
    params->width = texData->extraParam & 0x7ff;
    params->height = (texData->extraParam >> 11) & 0x7ff;
    params->imageParam = (texData->texImageParam + texKey) | 0x20000000;
    params->paletteBase = (u16)(plttOffset + plttKey);
}
