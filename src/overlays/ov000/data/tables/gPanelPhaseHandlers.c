#include "nitro/types.h"

extern void ApplyPanelSelection(void); /* ApplyPanelSelection */

void (*gPanelPhaseHandlers[1])(void) = {
    ApplyPanelSelection, /* ApplyPanelSelection */
};
