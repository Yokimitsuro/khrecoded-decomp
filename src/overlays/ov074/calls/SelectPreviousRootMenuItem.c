#include "nitro/types.h"

extern u16 data_02060500;
extern u32 PlaySoundEffect();

void SelectPreviousRootMenuItem(u8 *context)

{
  if (context[3] != '\0') {
    return;
  }
  if (*context == '\0') {
    if ((data_02060500 & 0x40) == 0) {
      return;
    }
    *context = context[1];
  }
  *context = *context + -1;
  PlaySoundEffect(0,0);
  context[2] = '\x01';
  return;
}
