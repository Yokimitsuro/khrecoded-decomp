#include "src/overlays/ov001/panel_state.h"

void SetPanelSessionActive(void)
{
    data_ov001_020a04e8->sessionActive = TRUE;
}
