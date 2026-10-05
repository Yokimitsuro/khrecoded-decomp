#include "nitro/types.h"

extern u16 data_02060500;

BOOL IsButtonBPressed(void)
{
    return (data_02060500 & 2) != 0;
}
