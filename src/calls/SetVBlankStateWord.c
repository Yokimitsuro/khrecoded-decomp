#include "nitro/types.h"

extern u32 gVBlankCallbackState;

u32 SetVBlankStateWord(u32 value)
{
    gVBlankCallbackState = value;
    return value;
}
