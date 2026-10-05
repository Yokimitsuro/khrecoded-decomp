#include "nitro/types.h"

extern u32 data_ov034_020c0fa0[2];
#define resultsWork ((int)data_ov034_020c0fa0[1])
extern u32 IsGlobalPackedBitSet();
extern u32 SetGlobalPackedBit();

void AdvanceResultsTransition(int mode,int transition)

{
  int result;
  
  result = IsGlobalPackedBitSet(transition + 0xf50);
  if (result == 0) {
    SetGlobalPackedBit(transition + 0xf50);
    *(int *)(resultsWork + 0x6bd8) = mode + 1;
    *(u32 *)(resultsWork + 0x6bf8) = 0;
    *(u32 *)(resultsWork + 0x6bb0) = 0;
  }
  return;
}
