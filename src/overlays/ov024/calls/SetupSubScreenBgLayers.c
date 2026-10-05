#include "nitro/types.h"

extern void GXS_SetGraphicsMode(int bgMode);

void SetupSubScreenBgLayers(void) {
    GXS_SetGraphicsMode(0);

    *(vu16 *)0x04001008 = (*(vu16 *)0x04001008 & 0x43) | 0xc00;
    *(vu16 *)0x0400100a = (*(vu16 *)0x0400100a & 0x43) | 0xd00;
    *(vu16 *)0x0400100c = (*(vu16 *)0x0400100c & 0x43) | 0xe00;
    *(vu16 *)0x0400100e = (*(vu16 *)0x0400100e & 0x43) | 0x4f00;

    *(vu16 *)0x04001008 = (*(vu16 *)0x04001008 & ~3);
    *(vu16 *)0x0400100a = (*(vu16 *)0x0400100a & ~3) | 2;
    *(vu16 *)0x0400100c = (*(vu16 *)0x0400100c & ~3) | 1;
    *(vu16 *)0x0400100e = (*(vu16 *)0x0400100e & ~3) | 3;
}
