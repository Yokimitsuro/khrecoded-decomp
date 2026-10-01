#include "libs/nitro/os/os_system_work_internal.h"

const OSBootInfo *OS_GetBootInfo(void)
{
    return HW_WM_BOOT_BUF;
}