#include "nitro/types.h"

extern int data_020608c8;

void SetParamWord20(int value)
{
    *(int *)((char *)&data_020608c8 + 0x14) = value;
}
