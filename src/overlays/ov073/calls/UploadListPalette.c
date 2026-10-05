#include "nitro/types.h"

typedef struct ListView {
    u8 pad_00[0x10];
    u16 palette[0x30];
} ListView;

extern void DC_FlushRange(const void *addr, u32 size);
extern void GXS_LoadBGPltt(const void *source, u32 offset, u32 size);
extern int NNS_GfdRegisterNewVramTransferTask(int type, int destOffset, void *source, int size);

void UploadListPalette(ListView *list, BOOL immediate)
{
    if (immediate) {
        DC_FlushRange(list->palette, sizeof(list->palette));
        GXS_LoadBGPltt(list->palette, 0xa0, sizeof(list->palette));
        return;
    }
    NNS_GfdRegisterNewVramTransferTask(0x1f, 0xa0, list->palette, sizeof(list->palette));
}
