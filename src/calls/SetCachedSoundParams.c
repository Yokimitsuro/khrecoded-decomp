#include "nitro/types.h"

extern u8 *data_0206084c;

void SetCachedSoundParams(u32 param1, u32 param2, u16 param3)
{
    *(u32 *)(data_0206084c + 0xb4720) = param1;
    *(u32 *)(data_0206084c + 0xb4724) = param2;
    *(u16 *)(data_0206084c + 0xb4728) = param3;
}
