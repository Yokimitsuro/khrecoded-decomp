#include "nitro/types.h"

extern int data_ov021_020b56c4[];
#define activeContext_020b56ac data_ov021_020b56c4[2]
extern u32 VEC_Mag();

u32 ScriptOp_GetObjectVectorMagnitude(int context)

{
  int object;
  u32 magnitude;
  
  object = activeContext_020b56ac;
  if (activeContext_020b56ac == 0) {
    return 0;
  }
  *(u16 *)(context + 0x2c) = 0x10;
  magnitude = VEC_Mag(object + 0x368);
  *(u32 *)(context + 0x30) = magnitude;
  return 0;
}
