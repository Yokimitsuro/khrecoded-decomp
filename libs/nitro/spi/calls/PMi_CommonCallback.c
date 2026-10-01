#include "libs/nitro/spi/pm_power_internal.h"

void PMi_CommonCallback(int tag, u32 data, BOOL error)
{
    u16 command = (u16)((data & SPI_PXI_RESULT_COMMAND_MASK) >>
                        SPI_PXI_RESULT_COMMAND_SHIFT);
    u16 pxiResult = (u16)(data & SPI_PXI_RESULT_DATA_MASK);

    if (error) {
        switch (command) {
        case SPI_PXI_COMMAND_PM_UTILITY:
        case SPI_PXI_COMMAND_PM_SLEEP_START:
            pxiResult = PM_BUSY;
            break;
        default:
            pxiResult = PM_ERROR;
            break;
        }
        PMi_CallCallbackAndUnlock(pxiResult);
        return;
    }

    switch (command) {
    case SPI_PXI_COMMAND_PM_SLEEP_START:
        break;
    case SPI_PXI_COMMAND_PM_UTILITY:
        if (PMi_Bss.work.work != 0) {
            *PMi_Bss.work.work = pxiResult;
        }
        pxiResult = PM_SUCCESS;
        break;
    case SPI_PXI_COMMAND_PM_SYNC:
        pxiResult = PM_SUCCESS;
        break;
    case SPI_PXI_COMMAND_PM_SLEEP_END:
        PMi_Bss.sleepEndFlag = 1;
        break;
    }

    PMi_CallCallbackAndUnlock(pxiResult);
}
