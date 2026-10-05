#include "nitro/types.h"

extern struct { int reserved; int context; } data_ov032_020c0080;
#define activeGroup data_ov032_020c0080.context
extern u32 func_ov001_02063130();
extern u32 func_ov001_0206430c();
extern u32 func_ov001_0206a814();

u32 CommitGroupActionState(void)

{
  int ready;
  
  ready = func_ov001_0206a814();
  if (ready != 0) {
    func_ov001_02063130(0xfffffffd,3);
    func_ov001_0206430c();
    *(u32 *)(activeGroup + 0x34) = 1;
    return 7;
  }
  return 0xffffffff;
}
