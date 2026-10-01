#include "libs/nitro/os/os_types_internal.h"

enum {
    HW_PLTT = 0x05000000,
    HW_DB_OAM_END = 0x07000800
};

BOOL OS_IsOnVram(const void *address)
{
    if ((u32)address >= HW_PLTT) {
        if ((u32)address < HW_DB_OAM_END) {
            return 1;
        }
    }
    return 0;
}