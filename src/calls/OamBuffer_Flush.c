#include "nitro/types.h"

typedef struct {
    u32 attr01;
    u32 attr23;
} OamEntry;

typedef struct {
    u8 pad_0000[0x4608];
    s32 engine;
    u8 pad_460c[0x6028 - 0x460c];
    s32 oamCount;
    s32 hiddenFrom;
    u8 pad_6030[4];
    OamEntry oams[128];
} OamBuffer;

extern void DC_FlushRange(void *start, u32 size);
extern void GX_LoadOAM(void *src, u32 offset, u32 size);
extern void GXS_LoadOAM(const void *src, u32 offset, u32 size);
extern int NNS_GfdRegisterNewVramTransferTask(s32 engine, int offset, void *src, int size);

static inline void HideOam(OamEntry *oam)
{
    oam->attr01 = (oam->attr01 & ~0x300) | 0x200;
}

void OamBuffer_Flush(OamBuffer *buffer, BOOL immediate)
{
    OamEntry *oams;
    int i = buffer->hiddenFrom;

    if (i < buffer->oamCount) {
        oams = buffer->oams;

        do {
            oams[i].attr01 = (oams[i].attr01 & ~0x300) | 0x200;
            i++;
        } while (i < buffer->oamCount);
    }
    buffer->hiddenFrom = 0;
    if (immediate) {
        DC_FlushRange(buffer->oams, 0x400);
        if (buffer->engine == 0x12) {
            GX_LoadOAM(buffer->oams, 0, buffer->oamCount << 3);
        } else {
            GXS_LoadOAM(buffer->oams, 0, buffer->oamCount << 3);
        }
    } else {
        NNS_GfdRegisterNewVramTransferTask(buffer->engine, 0, buffer->oams, buffer->oamCount << 3);
    }
}
