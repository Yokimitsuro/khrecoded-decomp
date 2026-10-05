#include "nitro/types.h"

extern void func_ov000_020622b8(void); /* ApplyPanelSelection */

void (*gPanelPhaseHandlers[1])(void) = {
    func_ov000_020622b8, /* ApplyPanelSelection */
};
