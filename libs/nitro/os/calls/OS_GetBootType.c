#include "libs/nitro/os/os_system_work_internal.h"

OSBootType OS_GetBootType(void)
{
    return OS_GetBootInfo()->bootType;
}