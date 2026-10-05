#include "nitro/types.h"

#define LEVEL_FILE(archive, index) ((((archive) + 0x8000) & 0xfffffc) << 7 | 0x80000000 | ((index) & 0x1ff))

typedef struct TextureDrawParams {
    u32 unk0;
    u32 unk4;
    u32 unk8;
} TextureDrawParams;

typedef struct ArchiveContext {
    u8 pad[8];
    u32 archives[0x3f];
    u16 unk104;
    u16 archiveIndex;
} ArchiveContext;

extern void *Archive_LoadFile(u32 fileId, u32 heapId);
extern s32 ValidateResourceTagAndDispatch(void *resource, void *heap);
extern void GetTextureDrawParams(TextureDrawParams *params, void *file, u32 texIndex);
extern void NNSi_FndFreeFromDefaultHeap(void *block);

void LoadTextureDrawParamsFromArchive(ArchiveContext *context, u32 fileIndex, TextureDrawParams *params, int count, int firstTexture) {
    void *file;
    int i;

    file = Archive_LoadFile(LEVEL_FILE(context->archives[context->archiveIndex], fileIndex), 0x11);
    i = 0;
    ValidateResourceTagAndDispatch(file, NULL);
    for (; i < count; i++) {
        GetTextureDrawParams(&params[i], file, (u8)(i + firstTexture));
    }
    NNSi_FndFreeFromDefaultHeap(file);
}
