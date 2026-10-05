#include "nitro/types.h"

extern int data_ov039_020bea20;

BOOL IsStatePhaseActive(void)
{
    int base = data_ov039_020bea20;
    int phase;
    BOOL active;

    if (base == 0) {
        return FALSE;
    }
    phase = *(int *)(base + 0xc9c4);
    active = TRUE;
    if (phase != 1 && phase != 2) {
        active = FALSE;
    }
    return active ? TRUE : FALSE;
}
