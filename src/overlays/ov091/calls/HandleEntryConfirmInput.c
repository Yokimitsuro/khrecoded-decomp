#include "nitro/types.h"

extern u16 data_02060500;
extern u32 data_ov091_020c375c;
extern u32 PlaySoundEffect();
extern u32 func_ov039_020bca20();
extern u32 SetPopupSlotVisible();
extern u32 SetPopupState();

void HandleEntryConfirmInput(u32 context)

{
  int result;
  
  result = func_ov039_020bca20();
  if (((((data_02060500 & 1) == 0) && ((data_02060500 & 2) == 0)) && ((data_02060500 & 8) == 0))
     && ((*(u16 *)(result + 8) & 3) != 1)) {
    return;
  }
  SetPopupSlotVisible(*(u32 *)(data_ov091_020c375c + 0x10),0);
  PlaySoundEffect(0,7);
  SetPopupState(context,6);
  return;
}
