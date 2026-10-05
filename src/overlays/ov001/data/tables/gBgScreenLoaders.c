#include "nitro/types.h"

extern void GX_LoadBG1Scr(void);
extern void GX_LoadBG2Scr(void);
extern void GX_LoadBG3Scr(void);
extern void GXS_LoadBG0Scr(void);
extern void GXS_LoadBG1Scr(void);
extern void GXS_LoadBG2Scr(void);
extern void GXS_LoadBG3Scr(void);

void (*gBgScreenLoaders[7])(void) = {
    GX_LoadBG1Scr,
    GX_LoadBG2Scr,
    GX_LoadBG3Scr,
    GXS_LoadBG0Scr,
    GXS_LoadBG1Scr,
    GXS_LoadBG2Scr,
    GXS_LoadBG3Scr,
};
