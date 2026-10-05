#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct SpriteSlot {
    s16 texWidth;
    s16 texHeight;
    u16 drawWidth;
    u16 drawHeight;
    u32 texImageParam;
    u32 texPaletteBase;
    fx32 extentX;
    fx32 extentY;
    fx32 scaleX;
    fx32 scaleY;
    u32 unk_20;
    u8 pad_24;
    u8 unk_25;
    u16 unk_26;
    u16 unk_28;
    u8 flags;
    u8 pad_2b;
    void *resource;
} SpriteSlot;

typedef struct TextureResource {
    u8 pad_00[8];
    u32 texDataOffset;
    u8 pad_0c[0x20];
    u32 paletteDataOffset;
    u8 pad_30[4];
    u16 paletteSectionOffset;
    u8 pad_36[6];
    u8 textureSection[1];
} TextureResource;

extern void *Archive_LoadFile(u32 fileId, u32 mode);
extern void LoadSceneTextureResource(void *file);
extern TextureResource *NNS_G3dGetTex(void *resource);
extern void NNSi_FndFreeFromDefaultHeap(void *block);

static inline void *GetResourceSection(u8 *section, u32 index)
{
    u32 stride;
    u8 *table;

    if (section != NULL && index < section[1]) {
        table = section + *(u16 *)(section + 6);
        stride = *(u16 *)table;
        return table + 4 + stride * index;
    }
    return NULL;
}

void LoadSlotTextureFile(SpriteSlot *slot, u32 fileId)
{
    TextureResource *resource;
    u32 *texInfo;
    u16 *paletteInfo;
    u32 paletteOffset;
    u32 paletteBase;
    u32 dataBase;

    slot->resource = Archive_LoadFile(fileId, 2);
    LoadSceneTextureResource(slot->resource);
    slot->flags = (u8)(slot->flags & ~0xe0);

    resource = NNS_G3dGetTex(slot->resource);
    if (resource != NULL) {
        texInfo = GetResourceSection(resource->textureSection, 0);
    } else {
        texInfo = NULL;
    }

    if (resource != NULL && resource->paletteSectionOffset != 0) {
        paletteInfo = GetResourceSection((u8 *)resource + resource->paletteSectionOffset, 0);
    } else {
        paletteInfo = NULL;
    }

    paletteOffset = paletteInfo[0];
    paletteBase = resource->paletteDataOffset & 0xffff;
    dataBase = resource->texDataOffset & 0xffff;
    slot->texWidth = texInfo[1] & 0x7ff;
    slot->texHeight = (texInfo[1] >> 0xb) & 0x7ff;
    slot->texImageParam = (texInfo[0] + dataBase) | 0x20000000;
    slot->texPaletteBase = ((paletteOffset >> 1) + (paletteBase >> 1)) & 0xffff;
    slot->drawWidth = slot->texWidth;
    slot->drawHeight = slot->texHeight;
    slot->unk_20 = 0;
    slot->unk_25 = 0;
    slot->scaleX = 0x1000;
    slot->scaleY = 0x1000;
    slot->unk_28 = 0;
    slot->unk_26 = slot->unk_28;
    slot->flags = (slot->flags & ~0x1f) | 0x1f;

    NNSi_FndFreeFromDefaultHeap(slot->resource);
    slot->resource = NULL;
    slot->extentX = 0x14000;
    slot->extentY = 0x14000;
}
