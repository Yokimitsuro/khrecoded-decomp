#include "nitro/types.h"

extern u8 *data_0206084c;

void ClearStreamFlag(int index)
{
    *(u8 *)(data_0206084c + index * 8 + 0xb44ce) = 0;
}
