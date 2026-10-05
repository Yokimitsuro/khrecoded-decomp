#include "nitro/types.h"

extern void GX_LoadBG0Char(void);
extern void GX_LoadBG1Char(void);
extern void GX_LoadBG2Char(void);
extern void GX_LoadBG3Char(void);
extern void GXS_LoadBG0Char(void);
extern void GXS_LoadBG1Char(void);
extern void GXS_LoadBG2Char(void);
extern void GXS_LoadBG3Char(void);

void (*gTextSceneBgCharacterLoaders[8])(void) = {
    GX_LoadBG0Char,
    GX_LoadBG1Char,
    GX_LoadBG2Char,
    GX_LoadBG3Char,
    GXS_LoadBG0Char,
    GXS_LoadBG1Char,
    GXS_LoadBG2Char,
    GXS_LoadBG3Char,
};
