#include "src/overlays/ov001/panel_state.h"

void RequestPanelFallback(void)
{
    data_ov001_020a04e8->fallbackRequested = TRUE;
}
