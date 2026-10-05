#include "nitro/types.h"

extern u8 gScriptState;

u32 SetScriptBusyFlag(u32 busy)
{
    gScriptState = (u8)busy;
    return busy;
}
