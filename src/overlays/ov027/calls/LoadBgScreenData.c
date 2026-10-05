#include "nitro/types.h"

extern void GX_LoadBG1Scr(const void *src, u32 offset, u32 size);
extern void GX_LoadBG2Scr(const void *src, u32 offset, u32 size);
extern void GX_LoadBG3Scr(const void *src, u32 offset, u32 size);
extern void GXS_LoadBG0Scr(const void *src, u32 offset, u32 size);
extern void GXS_LoadBG1Scr(const void *src, u32 offset, u32 size);
extern void GXS_LoadBG2Scr(const void *src, u32 offset, u32 size);
extern void GXS_LoadBG3Scr(const void *src, u32 offset, u32 size);

BOOL LoadBgScreenData(int bgId, u32 offset, const void *src, u32 size)
{
    BOOL loaded = TRUE;

    switch (bgId) {
    case 9:
        GX_LoadBG1Scr(src, offset, size);
        break;
    case 10:
        GX_LoadBG2Scr(src, offset, size);
        break;
    case 11:
        GX_LoadBG3Scr(src, offset, size);
        break;
    case 24:
        GXS_LoadBG0Scr(src, offset, size);
        break;
    case 25:
        GXS_LoadBG1Scr(src, offset, size);
        break;
    case 26:
        GXS_LoadBG2Scr(src, offset, size);
        break;
    case 27:
        GXS_LoadBG3Scr(src, offset, size);
        break;
    default:
        loaded = FALSE;
        break;
    }
    return loaded;
}
