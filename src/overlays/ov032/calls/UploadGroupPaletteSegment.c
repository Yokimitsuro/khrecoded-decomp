#include "nitro/types.h"

extern u32 data_ov032_020c0064;
extern u32 data_ov032_020c006e;
extern u32 NNS_GfdRegisterNewVramTransferTask();

void UploadGroupPaletteSegment(int alternate)

{
  u8 *palette;
  
  palette = &data_ov032_020c006e;
  if (alternate == 0) {
    palette = &data_ov032_020c0064;
  }
  NNS_GfdRegisterNewVramTransferTask((void *)0xf,0x184,(int)palette,10);
  return;
}
