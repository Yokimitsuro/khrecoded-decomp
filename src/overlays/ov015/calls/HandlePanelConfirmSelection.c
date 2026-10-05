#include "nitro/types.h"

extern u32 SetPanelTransitionMode();
extern u32 WH_SetError();

void HandlePanelConfirmSelection(int context)

{
  if (*(u16 *)(context + 2) != 0) {
    WH_SetError();
    return;
  }
  SetPanelTransitionMode(1);
  return;
}
