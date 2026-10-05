#include "nitro/types.h"

extern int data_ov032_020c0080[];
#define activeContext_020c0064 data_ov032_020c0080[1]
extern u32 func_ov001_0207ed54();
extern u32 func_ov001_020871a0();

u32 AcknowledgeGroupTransition(void)

{
  int ready;
  
  ready = func_ov001_0207ed54();
  if (ready == 0) {
    return 0xffffffff;
  }
  func_ov001_020871a0();
  *(u16 *)(activeContext_020c0064 + 6) = *(u16 *)(activeContext_020c0064 + 6) | 0x8000;
  return 3;
}
