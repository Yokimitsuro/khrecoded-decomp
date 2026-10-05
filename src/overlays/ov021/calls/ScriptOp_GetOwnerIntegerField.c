#include "nitro/types.h"

extern int data_ov021_020b56c4[];
#define activeContext_020b56a8 data_ov021_020b56c4[1]

u32 ScriptOp_GetOwnerIntegerField(int context)

{
  int owner;
  
  owner = activeContext_020b56a8;
  if (activeContext_020b56a8 == 0) {
    return 0;
  }
  *(u16 *)(context + 0x2c) = 1;
  *(int *)(context + 0x30) =
       (int)(*(int *)(owner + 0x18) + ((u32)(*(int *)(owner + 0x18) >> 0xb) >> 0x14)) >> 0xc;
  return 0;
}
