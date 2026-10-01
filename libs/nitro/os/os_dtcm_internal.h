#ifndef NITRO_OS_DTCM_INTERNAL_H
#define NITRO_OS_DTCM_INTERNAL_H

#include "libs/nitro/os/os_types_internal.h"

extern u32 SDK_AUTOLOAD_DTCM_START[];

#define HW_DTCM ((u32)SDK_AUTOLOAD_DTCM_START)
#define HW_DTCM_SYSRV (HW_DTCM + 0x3fc0)
#define HW_INTR_CHECK_BUF (HW_DTCM_SYSRV + 0x38)

#endif