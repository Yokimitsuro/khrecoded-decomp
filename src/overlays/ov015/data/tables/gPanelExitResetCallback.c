#include "nitro/types.h"

extern void ResetPanelExitFlags(void); /* ResetPanelExitFlags */

void (*gPanelExitResetCallback[1])(void) = {
    ResetPanelExitFlags, /* ResetPanelExitFlags */
};
