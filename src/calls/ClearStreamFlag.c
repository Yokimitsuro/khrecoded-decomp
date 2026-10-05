#include "nitro/types.h"

extern u8 *gSoundWork;

void ClearStreamFlag(int index)
{
    *(u8 *)(gSoundWork + index * 8 + 0xb44ce) = 0;
}
