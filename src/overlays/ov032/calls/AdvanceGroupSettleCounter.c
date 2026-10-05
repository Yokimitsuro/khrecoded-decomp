#include "nitro/types.h"

extern u32 GetRowCycleLimit();
extern u32 func_ov032_020bbc80();
extern u32 func_ov032_020bbc98();

void AdvanceGroupSettleCounter(int object)

{
  u16 linkedId;
  int member;
  int group;
  
  member = func_ov032_020bbc98(object);
  group = func_ov032_020bbc80(object);
  *(short *)(group + 0x1a) = *(short *)(group + 0x1a) + 1;
  if (0x3c <= *(short *)(group + 0x1a)) {
    *(u32 *)(group + 8) = *(u32 *)(group + 8) & 0xfffffffe | 1;
    linkedId = GetRowCycleLimit(*(u32 *)(object + 4),(int)*(char *)(member + 2));
    *(u16 *)(group + 0x12) = linkedId;
  }
  return;
}
