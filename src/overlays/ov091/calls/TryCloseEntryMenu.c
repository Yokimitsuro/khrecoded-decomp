#include "nitro/types.h"

extern u32 PlaySoundEffect();
extern u32 StartSubScene();
extern u32 PopStackEntry();
extern u32 func_ov091_020c1774();

void TryCloseEntryMenu(void)

{
  int result;
  
  result = func_ov091_020c1774();
  if (result != 0) {
    return;
  }
  PopStackEntry();
  StartSubScene(0,0xffffffff,1);
  PlaySoundEffect(0,3);
  return;
}
