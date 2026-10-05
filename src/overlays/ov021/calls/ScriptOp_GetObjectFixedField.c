#include "nitro/types.h"

extern int data_ov021_020b56c4[];
#define activeContext_020b56ac data_ov021_020b56c4[2]

u32 ScriptOp_GetObjectFixedField(int context)

{
  int object;
  
  object = activeContext_020b56ac;
  if (activeContext_020b56ac == 0) {
    return 0;
  }
  *(u16 *)(context + 0x2c) = 0x10;
  *(u32 *)(context + 0x30) = *(u32 *)(object + 0x29c);
  return 0;
}
