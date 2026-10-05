#include "nitro/types.h"

typedef struct {
    u8 pad00[0x10];
    u32 remaining;
    u32 vramOffset;
    const void *source;
} TextureUpload;

extern void OS_WaitVBlankIntr(void);
extern void GX_BeginLoadTex(void);
extern void GX_LoadTex(const void *src, u32 destSlotAddr, u32 size);
extern void GX_EndLoadTex(void);

BOOL StepTextureUpload(TextureUpload *upload)
{
    u32 size = upload->remaining;

    if (size >= 0x400) {
        size = 0x400;
    }
    OS_WaitVBlankIntr();
    GX_BeginLoadTex();
    GX_LoadTex(upload->source, upload->vramOffset, size);
    GX_EndLoadTex();
    upload->vramOffset += size;
    upload->source = (const u8 *)upload->source + size;
    upload->remaining -= size;
    if (upload->remaining == 0) {
        return TRUE;
    }
    return FALSE;
}
