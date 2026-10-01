#include "libs/nitro/mi/mi_dma_internal.h"

void MI_StopAllDma(void)
{
    MI_StopDma(0);
    MI_StopDma(1);
    MI_StopDma(2);
    MI_StopDma(3);
}