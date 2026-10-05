#include "nitro/types.h"

extern void func_ov095_020c1234(void);
extern void EnterPanelState2(void);
extern void UpdateGridScrollDisplay(void);

void (*const gItemReportStateHandlers[3])(void) = {
    func_ov095_020c1234,
    EnterPanelState2,
    UpdateGridScrollDisplay,
};
