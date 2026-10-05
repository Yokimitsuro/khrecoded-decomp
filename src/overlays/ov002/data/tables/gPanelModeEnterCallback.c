#include "nitro/types.h"

extern void RefreshMenuContext(void); /* RefreshMenuContext */

void (*gPanelModeEnterCallback[1])(void) = {
    RefreshMenuContext, /* RefreshMenuContext */
};
