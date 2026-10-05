#include "nitro/types.h"

extern int data_ov032_020c0080[];
#define activeContext_020c0064 data_ov032_020c0080[1]
extern u32 func_ov001_0206a814();

u32 FinishGroupActionState(void)

{
  int ready;
  
  ready = func_ov001_0206a814();
  if (ready != 0) {
    *(u16 *)(activeContext_020c0064 + 6) = *(u16 *)(activeContext_020c0064 + 6) | 0x8000;
    return 0x10;
  }
  return 0xffffffff;
}
