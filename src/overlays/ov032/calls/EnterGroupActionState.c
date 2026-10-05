#include "nitro/types.h"

extern int data_ov032_020c0080[];
#define activeContext_020c0064 data_ov032_020c0080[1]
extern u32 StartIdleSceneObjects();
extern u32 func_ov001_02087650();

u32 EnterGroupActionState(void)

{
  int group;
  
  group = activeContext_020c0064;
  *(u16 *)(activeContext_020c0064 + 6) = *(u16 *)(activeContext_020c0064 + 6) | 0x20;
  if ((*(u16 *)(group + 6) & 0x10) == 0) {
    StartIdleSceneObjects();
    func_ov001_02087650(1);
  }
  return 0xe;
}
