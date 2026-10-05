#include "nitro/types.h"

extern void func_ov013_020717c0(void); /* ResolvePanelExitMode */

void (*gPanelExitModeResolver[1])(void) = {
    func_ov013_020717c0, /* ResolvePanelExitMode */
};
