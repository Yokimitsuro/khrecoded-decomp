#include "nitro/types.h"

extern void func_ov015_02070b60(void); /* ResetPanelExitFlags */

void (*gPanelExitResetCallback[1])(void) = {
    func_ov015_02070b60, /* ResetPanelExitFlags */
};
