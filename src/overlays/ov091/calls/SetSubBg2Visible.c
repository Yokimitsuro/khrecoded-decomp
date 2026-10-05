#include "nitro/types.h"

#define REG_DB_DISPCNT (*(vu32 *)0x04001000)

void SetSubBg2Visible(void *scene, BOOL visible)
{
    u32 planes = (REG_DB_DISPCNT & 0x1f00) >> 8;

    if (visible) {
        planes |= 4;
    } else {
        planes &= ~4;
    }
    REG_DB_DISPCNT = (REG_DB_DISPCNT & ~0x1f00) | (planes << 8);
}
