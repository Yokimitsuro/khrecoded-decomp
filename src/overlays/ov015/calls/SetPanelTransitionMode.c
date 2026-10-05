#include "nitro/types.h"

extern u8 data_ov015_0207e980[];
#define transitionMode (*(u32 *)(data_ov015_0207e980 + 0x50))

void SetPanelTransitionMode(u32 mode)

{
  transitionMode = mode;
  return;
}
