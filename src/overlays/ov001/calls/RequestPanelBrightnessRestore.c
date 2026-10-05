#include "src/overlays/ov001/panel_state.h"

void RequestPanelBrightnessRestore(void)
{
    data_ov001_020a04e8->brightnessRestoreRequested = TRUE;
}
