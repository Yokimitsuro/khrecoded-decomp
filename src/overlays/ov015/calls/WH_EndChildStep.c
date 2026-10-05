#include "nitro/types.h"

extern char data_ov015_0207f3a0[];
extern int PXI_Init_02012298(void *arg);
extern void WH_SetError(int code);
extern int func_ov015_02073cbc(void);
extern void PollPanelTransition(void);

BOOL WH_EndChildStep(void)
{
    int error = PXI_Init_02012298(data_ov015_0207f3a0);

    if (error != 0) {
        WH_SetError(error);
        return FALSE;
    }
    if (func_ov015_02073cbc() != 0) {
        return TRUE;
    }
    PollPanelTransition();
    return FALSE;
}
