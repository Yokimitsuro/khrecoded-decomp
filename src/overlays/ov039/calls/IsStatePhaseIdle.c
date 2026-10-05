#include "nitro/types.h"

extern int data_ov039_020bea20;

BOOL IsStatePhaseIdle(void)
{
    int base = data_ov039_020bea20;

    if (base == 0) {
        return 1;
    }
    return *(int *)(base + 0xc9c4) == 0;
}
