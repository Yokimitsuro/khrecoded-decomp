#include "nitro/types.h"

extern void GX_LoadBG0Char(void);
extern void GX_LoadBG1Char(void);
extern void GX_LoadBG2Char(void);
extern void GX_LoadBG3Char(void);

void (*const gBgCharacterLoaders[4])(void) = {
    GX_LoadBG0Char,
    GX_LoadBG1Char,
    GX_LoadBG2Char,
    GX_LoadBG3Char,
};
