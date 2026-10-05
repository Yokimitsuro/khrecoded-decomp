#include "nitro/types.h"

extern signed char func_ov001_02068084(void);

void GetModeDataRegion(u32 *offset, u32 *size) {
    switch (func_ov001_02068084()) {
    case 0:
        *offset = 0x500;
        *size = 8;
        return;
    case 1:
        *offset = 0x508;
        *size = 0x10;
        return;
    case 2:
        *offset = 0x518;
        *size = 0x10;
        return;
    case 3:
        *offset = 0x528;
        *size = 0x18;
        return;
    case 4:
        *offset = 0x540;
        *size = 0x10;
        return;
    case 5:
        *offset = 0x550;
        *size = 0x10;
        return;
    case 6:
        *offset = 0x560;
        *size = 0x10;
        return;
    case 7:
        *offset = 0x570;
        *size = 0x10;
        return;
    case 8:
        *offset = 0xffffffff;
        *size = 0xffffffff;
    }
}
