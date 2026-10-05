#include "nitro/types.h"

extern u16 data_02060500;

BOOL IsButtonXPressed(void)
{
    return (data_02060500 & 0x400) != 0;
}
