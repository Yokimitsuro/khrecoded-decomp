#include "nitro/types.h"

extern void ResolvePanelExitMode(void); /* ResolvePanelExitMode */

void (*gPanelExitModeResolver[1])(void) = {
    ResolvePanelExitMode, /* ResolvePanelExitMode */
};
