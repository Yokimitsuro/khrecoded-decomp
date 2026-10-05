#include "nitro/types.h"

extern u8 gPanelEnabled;

u32 SetPanelEnabled(u32 enabled)
{
    gPanelEnabled = (u8)enabled;
    return enabled;
}
