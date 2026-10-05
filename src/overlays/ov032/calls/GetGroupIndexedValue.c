#include "nitro/types.h"

extern int data_ov032_020c0080[];
#define activeContext_020c0064 data_ov032_020c0080[1]

u32 GetGroupIndexedValue(u32 index)

{
  if (index < 3) {
    index = (u32)*(u16 *)(activeContext_020c0064 + index * 2 + 0x44);
  }
  return index;
}
