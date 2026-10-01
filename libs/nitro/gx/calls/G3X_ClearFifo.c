#include "libs/nitro/os/os_types_internal.h"

extern void GXi_NopClearFifo128_(void *destination);

void G3X_ClearFifo(void)
{
    volatile u32 *fifo = (volatile u32 *)0x04000400;

    GXi_NopClearFifo128_((void *)fifo);
    while (*(volatile u32 *)0x04000600 & 0x08000000) {
    }
}