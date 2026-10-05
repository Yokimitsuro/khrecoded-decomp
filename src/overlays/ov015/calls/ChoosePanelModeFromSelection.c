#include "nitro/types.h"

extern u32 SetPanelTransitionMode();

void ChoosePanelModeFromSelection(int context)

{
  if (*(u16 *)(context + 2) != 0) {
    SetPanelTransitionMode(10);
    return;
  }
  SetPanelTransitionMode(0);
  return;
}
