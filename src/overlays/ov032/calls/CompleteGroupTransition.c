#include "nitro/types.h"

extern struct { int reserved; int context; } data_ov032_020c0080;
#define activeGroup data_ov032_020c0080.context
extern u32 StoreToGlobalPtr4Field28();
extern u32 func_ov001_0207b6b0();

u32 CompleteGroupTransition(void)

{
  int ready;
  
  ready = func_ov001_0207b6b0();
  if (ready == 0) {
    return 0xffffffff;
  }
  if ((*(u16 *)(activeGroup + 6) & 1) != 0) {
    *(u16 *)(activeGroup + 6) = *(u16 *)(activeGroup + 6) & 0xfffe;
  }
  StoreToGlobalPtr4Field28(0);
  return 7;
}
