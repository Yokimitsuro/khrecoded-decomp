#include "nitro/types.h"

typedef struct TextureParams {
    u32 imageParam;
    u32 paletteParam;
} TextureParams;

typedef struct PzTextureHost {
    u8 pad_00[4];
    TextureParams textures[7];
} PzTextureHost;

extern char sOv001_MoPzZ_0209ea14[];
extern PzTextureHost *data_ov001_020a0484;
extern void *SND_RegisterSeq(char *path, int heapId);
extern void func_0202c6a4(int useDefaultHooks);
extern void *AcquireOrRefreshResourceBlock(void *slot, void *textureHeader, int flag);
extern int IndexedPointer_GetFirstWord(void *resource, int recordIndex);
extern void *NestedPointer_GetFirstWord(void *resource, int recordIndex, int entryIndex);
extern int Tex0_GetTexPlttParams(TextureParams *params, void *texture, int reload);
extern int ReleaseSharedRecordSlot(void *slot);

void LoadPzTextureParams(void)
{
    void *slot;
    void *resource;
    int textureCount;
    int entryIndex;

    slot = SND_RegisterSeq(sOv001_MoPzZ_0209ea14, 5);
    func_0202c6a4(0);
    resource = AcquireOrRefreshResourceBlock(slot, NULL, 1);
    func_0202c6a4(1);
    textureCount = IndexedPointer_GetFirstWord(resource, 7);
    for (entryIndex = 0; entryIndex < textureCount; entryIndex++) {
        Tex0_GetTexPlttParams(&data_ov001_020a0484->textures[entryIndex], NestedPointer_GetFirstWord(resource, 7, entryIndex), 0);
    }
    ReleaseSharedRecordSlot(slot);
}
