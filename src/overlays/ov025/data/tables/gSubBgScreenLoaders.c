#include "nitro/types.h"

extern void GXS_LoadBG2Scr(void);
extern void GXS_LoadBG3Scr(void);

void (*gSubBgScreenLoaders[2])(void) = {
    GXS_LoadBG2Scr,
    GXS_LoadBG3Scr,
};
