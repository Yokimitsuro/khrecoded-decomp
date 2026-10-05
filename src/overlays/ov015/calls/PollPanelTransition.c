#include "nitro/types.h"

extern u8 data_ov015_0207e980[];
#define transitionMode (*(int *)(data_ov015_0207e980 + 0x50))
extern u32 data_ov015_0207fbc0;
extern u32 ClearSlotEventHandler();
extern u32 SetPanelTransitionMode();
extern u32 WH_SetError();
extern u32 func_ov015_020746f8();

void PollPanelTransition(void)

{
  int result;
  
  if ((transitionMode == 5) && (result = ClearSlotEventHandler(&data_ov015_0207fbc0), result != 0)) {
    WH_SetError();
  }
  result = func_ov015_020746f8();
  if (result != 0) {
    return;
  }
  SetPanelTransitionMode(10);
  return;
}
