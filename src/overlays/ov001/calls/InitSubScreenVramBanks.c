#include "nitro/types.h"

extern void GX_SetBankForBG(u32 mask);
extern void GX_SetBankForSubBG(u32 mask);
extern void GX_SetBankForSubOBJExtPltt(u32 mask);
extern void GX_SetBankForSubOBJ(u32 mask);
extern void ResetDisplayHardware(void);
extern void SetFieldVisiblePlanes(void);
extern void SetupFieldBgLayers(void);

void InitSubScreenVramBanks(void)
{
    ResetDisplayHardware();
    GX_SetBankForBG(0x10);
    GX_SetBankForSubBG(0x80);
    GX_SetBankForSubOBJ(0x100);
    GX_SetBankForSubOBJExtPltt(0);
    SetupFieldBgLayers();
    SetFieldVisiblePlanes();
}
