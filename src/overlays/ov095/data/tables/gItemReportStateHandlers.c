#include "nitro/types.h"

extern void func_ov095_020c1234(void);
extern void EnterPanelState2(void);
extern void func_ov095_020c1254(void);

void (*const gItemReportStateHandlers[3])(void) = {
    func_ov095_020c1234,
    EnterPanelState2,
    func_ov095_020c1254,
};
