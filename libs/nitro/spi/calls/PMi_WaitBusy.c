#include "libs/nitro/spi/pm_power_internal.h"

extern int OS_GetProcMode(void);
extern int OS_GetCpsrIrq(void);
extern void PXIi_HandlerRecvFifoNotEmpty(void);

#define REG_IME (*(volatile u16 *)0x04000208)
#define OS_PROCMODE_IRQ 0x12
#define OS_CPSR_IRQ_MASK 0x80

void PMi_WaitBusy(void)
{
    PMWork *work = &PMi_Work;

    if (!work->lock) {
        return;
    }

    do {
        if (((PMi_WaitBusyMethod & PMi_WAITBUSY_METHOD_CPUMODE)
             && OS_GetProcMode() == OS_PROCMODE_IRQ)
         || ((PMi_WaitBusyMethod & PMi_WAITBUSY_METHOD_CPSR)
             && OS_GetCpsrIrq() == OS_CPSR_IRQ_MASK)
         || ((PMi_WaitBusyMethod & PMi_WAITBUSY_METHOD_IME)
             && REG_IME == 0)) {
            PXIi_HandlerRecvFifoNotEmpty();
        }
    } while (work->lock);
}