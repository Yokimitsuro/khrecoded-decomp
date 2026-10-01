#include "libs/nitro/os/os_reset_internal.h"
#include "libs/nitro/os/os_system_work_internal.h"

void OS_Terminate(void);
u32 OS_GetLockID(void);
void CARD_LockRom(u16 lockId);
u32 OS_SetIrqMask(u32 mask);
u32 OS_ResetRequestIrqMask(u32 mask);
void MI_StopAllDma(void);
void OSi_SendToPxi(int command);

void OS_ResetSystem(u32 parameter)
{
    u16 lockId;

    if (HW_WM_BOOT_BUF->bootType == OS_BOOTTYPE_DOWNLOAD_MB) {
        OS_Terminate();
    }

    lockId = (u16)OS_GetLockID();
    CARD_LockRom(lockId);
    OS_SetIrqMask(OS_IE_FIFO_RECV);
    OS_ResetRequestIrqMask(~OS_IE_FIFO_RECV);
    MI_StopAllDma();
    HW_RESET_PARAMETER = parameter;
    OSi_SendToPxi(OS_PXI_COMMAND_RESET);
    HW_COMPONENT_PARAMETER = OSi_GetOriginalExceptionHandler();
    OSi_DoResetSystem();
}
