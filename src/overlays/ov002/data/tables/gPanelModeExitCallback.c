#include "nitro/types.h"

extern void DispatchMenuResult(void); /* DispatchMenuResult */

void (*gPanelModeExitCallback[1])(void) = {
    DispatchMenuResult, /* DispatchMenuResult */
};
