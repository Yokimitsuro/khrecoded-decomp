#include "nitro/types.h"

extern struct { int reserved; int context; } data_ov032_020c0080;
#define activeGroup data_ov032_020c0080.context
extern u32 func_ov001_0206685c();
extern u32 func_ov001_0206a7c0();
extern u32 func_ov001_0206a814();

u32 TryOpenGroupAction(void)

{
  int state;
  int ready;
  
  state = activeGroup;
  if (((*(u16 *)(activeGroup + 6) & 0x10) == 0) &&
     (ready = func_ov001_0206685c(), ready != 0)) {
    return 0xffffffff;
  }
  ready = func_ov001_0206a814();
  if (ready == 0) {
    return 0xffffffff;
  }
  func_ov001_0206a7c0((int)*(char *)(state + 8));
  return 0xf;
}
