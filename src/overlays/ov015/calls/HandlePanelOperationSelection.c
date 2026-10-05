#include "nitro/types.h"

extern u8 data_ov015_0207e980[];
#define operationHandle (*(u32 *)(data_ov015_0207e980 + 0x48))
extern u32 SetSessionCallback();
extern u32 SetPanelTransitionMode();
extern u32 WH_SetError();

void HandlePanelOperationSelection(int context)

{
  int result;
  
  if (*(u16 *)(context + 2) != 0) {
    WH_SetError();
    SetPanelTransitionMode(10);
    return;
  }
  result = SetSessionCallback(operationHandle);
  if (result != 0) {
    WH_SetError();
    SetPanelTransitionMode(10);
    return;
  }
  SetPanelTransitionMode(1);
  return;
}
