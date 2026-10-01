#include "libs/nitro/spi/pm_power_internal.h"

void PMi_SendPxiData(u32 data)
{
    while (PXI_SendWordByFifo(PXI_FIFO_TAG_PM, data, FALSE) !=
           PXI_FIFO_SUCCESS) {
    }
}