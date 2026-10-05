#include "nitro/types.h"

extern u8 data_ov015_0207e980[];
#define pendingValue (*(u32 *)(data_ov015_0207e980 + 0x4c))

void SetPanelPendingValue(u32 value)

{
  pendingValue = value;
  return;
}
