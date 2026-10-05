#include "nitro/types.h"

extern int data_ov032_020c0080[];
#define activeContext_020c0064 data_ov032_020c0080[1]
extern u32 func_ov001_0206a72c();
extern u32 func_ov032_020ba624();

u32 InitializeGroupAction(void)

{
  int group;
  
  group = activeContext_020c0064;
  func_ov001_0206a72c((int)*(char *)(activeContext_020c0064 + 8));
  *(u16 *)(group + 6) = *(u16 *)(group + 6) | 0x20;
  func_ov032_020ba624();
  return 10;
}
