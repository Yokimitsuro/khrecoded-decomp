#include "nitro/types.h"

extern int data_ov032_020c0080[];
#define activeContext_020c0064 data_ov032_020c0080[1]

u32 ClearGroupTransitionFlags(void)

{
  *(u16 *)(activeContext_020c0064 + 6) = *(u16 *)(activeContext_020c0064 + 6) & 0xfff3;
  return 0xffffffff;
}
