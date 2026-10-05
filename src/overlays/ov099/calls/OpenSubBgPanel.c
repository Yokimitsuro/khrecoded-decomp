#include "nitro/types.h"

extern void func_ov099_020bf838(int mode, u8 *work);
extern void PlaySoundEffect(int channel, int sound);

void OpenSubBgPanel(u8 *work) {
  u32 offset;

  if (*(int *)(work + 0xcf0c) != 0) {
    return;
  }
  *(int *)(work + 0xcf0c) = 1;
  offset = 0;
  if (*(int *)(work + 0xcf0c) == 1) {
    offset = 0x100;
  }
  *(vu32 *)0x04001018 = offset & 0x1ff;
  func_ov099_020bf838(1, work);
  PlaySoundEffect(0, 2);
}
