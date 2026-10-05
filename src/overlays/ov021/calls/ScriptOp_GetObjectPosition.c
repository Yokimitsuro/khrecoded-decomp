#include "nitro/types.h"

extern int data_ov021_020b56c4[];
#define activeContext_020b56ac data_ov021_020b56c4[2]

u32 ScriptOp_GetObjectPosition(int context)

{
  int object;
  
  object = activeContext_020b56ac;
  *(u32 *)(context + 0x34) = *(u32 *)(activeContext_020b56ac + 0x2c0);
  *(u32 *)(context + 0x38) = *(u32 *)(object + 0x2c4);
  *(u32 *)(context + 0x3c) = *(u32 *)(object + 0x2c8);
  return 0;
}
