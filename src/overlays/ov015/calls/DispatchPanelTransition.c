#include "nitro/types.h"

extern u32 GetPanelTransitionMode(void);
extern void func_ov015_02072ee4(char nextState);
extern BOOL WH_StartTransitionStep(void);
extern void WH_Finalize(void);

void DispatchPanelTransition(void)
{
    switch (GetPanelTransitionMode()) {
    case 9:
    case 10:
        WH_Finalize();
        break;
    case 1:
        WH_StartTransitionStep();
        break;
    case 0:
        func_ov015_02072ee4(1);
        break;
    case 3:
        break;
    default:
        WH_Finalize();
        break;
    }
}
