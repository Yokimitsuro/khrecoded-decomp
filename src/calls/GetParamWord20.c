#include "nitro/types.h"

extern int data_020608c8;

/* Reads param word 20. */
int GetParamWord20(void)
{
    return *(int *)((char *)&data_020608c8 + 0x14);
}
