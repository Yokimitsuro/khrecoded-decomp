#include "nitro/types.h"

extern struct { int reserved; int context; } data_ov032_020c0080;
#define activeGroup data_ov032_020c0080.context
extern u32 func_ov001_0206685c();
extern u32 BeginScreenFadeOut();
extern u32 IsScreenModeIdle();

u32 TryOpenGroupAction(void)

{
  int state;
  int ready;
  
  state = activeGroup;
  if (((*(u16 *)(activeGroup + 6) & 0x10) == 0) &&
     (ready = func_ov001_0206685c(), ready != 0)) {
    return 0xffffffff;
  }
  ready = IsScreenModeIdle();
  if (ready == 0) {
    return 0xffffffff;
  }
  BeginScreenFadeOut((int)*(char *)(state + 8));
  return 0xf;
}
