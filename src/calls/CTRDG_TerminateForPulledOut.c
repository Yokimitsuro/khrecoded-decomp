#include "nitro/types.h"
#include "nitro/os.h"
#include "nitro/pxi.h"
#include "nitro/ctrdg.h"

extern void OS_Terminate(void);
extern void CTRDGi_SendtoPxi(u32 data);

void CTRDG_TerminateForPulledOut(void)
{
    CTRDGi_SendtoPxi(CTRDG_PXI_COMMAND_TERMINATE);
    OS_Terminate();
}
