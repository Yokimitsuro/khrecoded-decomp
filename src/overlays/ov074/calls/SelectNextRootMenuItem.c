#include "nitro/types.h"

extern u16 data_02060500;
extern u32 PlaySoundEffect();

void SelectNextRootMenuItem(u8 *context)

{
  int previousSelection;
  
  if (context[3] != 0) {
    return;
  }
  if (++*context >= context[1]) {
    if ((data_02060500 & 0x80) == 0) {
      *context = context[1] - 1;
      return;
    }
    *context = 0;
  }
  PlaySoundEffect(0,0);
  context[2] = 1;
  return;
}
