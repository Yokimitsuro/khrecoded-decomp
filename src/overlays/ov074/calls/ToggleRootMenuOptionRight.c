#include "nitro/types.h"

extern u32 PlaySoundEffect();

void ToggleRootMenuOptionRight(int context)

{
  if (*(u8 *)(context + 3) != '\x01') {
    return;
  }
  *(u8 *)(context + 4) = *(u8 *)(context + 4) ^ 1;
  PlaySoundEffect(0,0);
  *(u8 *)(context + 2) = 1;
  return;
}
