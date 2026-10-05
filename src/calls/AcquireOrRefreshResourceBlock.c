#include "nitro/types.h"

typedef struct {
    u8 pad_00[2];
    u16 refCount;
    u16 loadCount;
    u8 pad_06[6];
    void *resource;
    void *cachedBlock;
} ResourceSlot;

extern u32 data_02056014;
extern void *NNS_G3dGetTex(const void *header);
extern void *NNS_FndAllocFromDefaultExpHeapEx(u32 size, int align);
extern int CallSelectionHandler(void *a, void *b);
extern s32 ValidateResourceTagAndDispatch(void *resource, void *heap);
extern void MI_CpuCopy8(const void *src, void *dst, u32 size);

void *AcquireOrRefreshResourceBlock(ResourceSlot *info, void *textureHeader, int flag)
{
    void *block = NULL;
    u32 savedGuard = data_02056014;
    BOOL foundFresh = FALSE;

    data_02056014 = flag;

    if (info->refCount == 0) {
        void *cached = info->cachedBlock;
        if (cached != NULL) {
            block = cached;
        } else if (textureHeader != NULL) {
            block = NNS_G3dGetTex(textureHeader);
            foundFresh = TRUE;
        }
        if (*(u32 *)info->resource == 0x4850414b) {
            CallSelectionHandler(info->resource, block);
        } else {
            ValidateResourceTagAndDispatch(info->resource, block);
        }
        if (foundFresh) {
            u32 size = *(u32 *)((u8 *)block + 0x14);
            void *allocated = NNS_FndAllocFromDefaultExpHeapEx(size, 0x20);
            info->cachedBlock = allocated;
            MI_CpuCopy8(block, allocated, size);
        }
    }

    info->refCount++;
    data_02056014 = savedGuard;
    if (flag != 0) {
        info->loadCount++;
    }
    return info->resource;
}
