#include "nitro/types.h"

extern u32 SetUnlockableElementsVisible();
extern u32 func_ov027_020ba2c8();

void ResetMatrixDescription(int context)

{
  void *description;
  
  *(u32 *)(context + 0x13ea0) = 0;
  *(u32 *)(context + 0x13ea4) = 0;
  SetUnlockableElementsVisible(*(void **)(context + 0x131a4),1);
  description = func_ov027_020ba2c8((void *)(context + 0x4ee0),0x58);
  *(void **)(context + 0x11fac) = description;
  *(u8 *)(context + 7) = 1;
  *(u32 *)(context + 0x68) = 1;
  return;
}
