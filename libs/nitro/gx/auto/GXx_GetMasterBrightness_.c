#include "libs/nitro/os/os_types_internal.h"

int GXx_GetMasterBrightness_(volatile u16 *reg)
{
    u16 mode = (u16)(*reg & 0xc000);

    if (mode == 0) {
        return 0;
    } else if (mode == 0x4000) {
        return *reg & 0x1f;
    } else if (mode == 0x8000) {
        return -(*reg & 0x1f);
    } else {
        return 0;
    }
}