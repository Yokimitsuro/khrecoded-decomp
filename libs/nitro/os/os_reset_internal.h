#ifndef NITRO_OS_RESET_INTERNAL_H
#define NITRO_OS_RESET_INTERNAL_H

#include "libs/nitro/os/os_types_internal.h"

#define OS_IE_FIFO_RECV 0x00040000
#define OS_PXI_COMMAND_RESET 16
#define HW_RESET_PARAMETER (*(volatile u32 *)0x02fffc20)
#define HW_COMPONENT_PARAMETER (*(volatile u32 *)0x02ffff9c)

void OS_InitReset(void);
void OS_ResetSystem(u32 parameter);
u32 OSi_GetOriginalExceptionHandler(void);
void OSi_DoResetSystem(void);

#endif
