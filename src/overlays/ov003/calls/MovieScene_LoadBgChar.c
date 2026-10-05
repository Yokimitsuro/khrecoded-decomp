#include "nitro/types.h"

typedef struct CharAsset {
    u8 pad_00[0x10];
    u32 size;
    void *data;
} CharAsset;

typedef struct AssetSlot {
    CharAsset *asset;
    u8 pad_04[8];
} AssetSlot;

typedef struct MovieScene {
    u8 pad_000[0x8dc];
    AssetSlot slots[1];
} MovieScene;

typedef struct BgRequest {
    u8 pad_00[6];
    u16 slot;
    u16 plane;
} BgRequest;

extern void GX_LoadBG0Char(const void *src, u32 offset, u32 size);
extern void GX_LoadBG1Char(const void *src, u32 offset, u32 size);
extern void GX_LoadBG2Char(const void *src, u32 offset, u32 size);

BOOL MovieScene_LoadBgChar(MovieScene *scene, void *unused, BgRequest *request)
{
    CharAsset *asset = scene->slots[request->slot].asset;

    switch (request->plane) {
    case 1:
        GX_LoadBG0Char(asset->data, 0, asset->size);
        break;
    case 2:
        GX_LoadBG1Char(asset->data, 0, asset->size);
        break;
    case 4:
        GX_LoadBG2Char(asset->data, 0, asset->size);
        break;
    }
    return TRUE;
}
