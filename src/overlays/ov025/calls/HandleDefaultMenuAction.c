#include "nitro/types.h"

extern u32 data_ov025_020b7780;
extern u32 PlaySoundEffect();
extern u32 func_ov001_02063a38();
extern u32 func_ov001_0207b348();
extern u32 func_ov001_0207b6dc();

void HandleDefaultMenuAction(void)

{
  int mode;
  
  if (*(u8 *)(data_ov025_020b7780 + 0x64e9) == '\0') {
    func_ov001_0207b6dc();
    mode = func_ov001_02063a38();
    func_ov001_0207b348(mode == 10);
    PlaySoundEffect(0,0x3b);
  }
  return;
}
