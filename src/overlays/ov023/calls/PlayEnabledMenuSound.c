#include "nitro/types.h"

extern u32 data_ov023_020b6f84;
extern u32 PlaySoundEffect();

void PlayEnabledMenuSound(void)

{
  if (*(int *)(data_ov023_020b6f84 + 0x40) != 0) {
    PlaySoundEffect(0,0x4a);
  }
  return;
}
