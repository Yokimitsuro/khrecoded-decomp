#include "nitro/types.h"

extern int data_ov032_020c0088[];
extern void SetGroupMenuProgress(int percent);

void SetGroupMenuPercent(int percent)
{
    int menu = data_ov032_020c0088[1];
    if (percent > 100) {
        percent = 100;
    } else if (percent < 0) {
        percent = 0;
    }
    if (percent != *(int *)(menu + 0x18)) {
        SetGroupMenuProgress(percent);
        *(int *)(menu + 0x18) = percent;
    }
}
