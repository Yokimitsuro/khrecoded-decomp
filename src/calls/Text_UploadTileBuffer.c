#include "nitro/types.h"

extern int NNS_GfdRegisterNewVramTransferTask(void *src, int size, int dest, int param);

typedef struct {
    u8 pad_00[0x24];
    int vramOffset;
} TextVramTarget;

typedef struct {
    u8 pad_00[0x20];
    TextVramTarget *target;
    void *tileBuffer;
    int uploadParam;
    u16 rowSize;
    u8 pad_2e[4];
    u8 rowCount;
} TextSurface;

void Text_UploadTileBuffer(TextSurface *surface)
{
    NNS_GfdRegisterNewVramTransferTask(surface->tileBuffer, surface->rowCount * surface->rowSize,
                                 surface->target->vramOffset, surface->uploadParam);
}
