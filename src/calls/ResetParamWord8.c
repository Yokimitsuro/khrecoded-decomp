#include "nitro/types.h"

extern int data_020608c8;

void ResetParamWord8(void)
{
    *(int *)((char *)&data_020608c8 + 8) = -1;
}
