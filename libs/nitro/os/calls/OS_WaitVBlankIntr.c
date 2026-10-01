#include "libs/nitro/os/os_types_internal.h"

extern void WaitByLoop(s32 count);
extern void OS_WaitIrq(BOOL clear, u32 irqFlags);

void OS_WaitVBlankIntr(void)
{
    WaitByLoop(1);
    OS_WaitIrq(1, 1);
}