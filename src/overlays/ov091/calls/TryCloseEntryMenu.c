#include "nitro/types.h"

extern u32 PlaySoundEffect();
extern u32 StartSubScene();
extern u32 func_ov039_020bc8c0();
extern u32 func_ov091_020c1774();

void TryCloseEntryMenu(void)

{
  int result;
  
  result = func_ov091_020c1774();
  if (result != 0) {
    return;
  }
  func_ov039_020bc8c0();
  StartSubScene(0,0xffffffff,1);
  PlaySoundEffect(0,3);
  return;
}
