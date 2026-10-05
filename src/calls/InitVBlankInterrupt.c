#include "nitro/types.h"

extern u32 gVBlankCallbackState;
extern void MI_CpuFill8(void *dst, int value, int size);
extern void OS_SetIrqFunction(u32 intrBits, void *function);
extern u32 OS_EnableIrqMask(u32 mask);
extern int GX_VBlankIntr(int enable);

void InitVBlankInterrupt(void) {
    MI_CpuFill8(&gVBlankCallbackState, 0, 0x114);
    OS_SetIrqFunction(1, (void *)0x1ff8000);
    OS_EnableIrqMask(1);
    GX_VBlankIntr(1);
}
