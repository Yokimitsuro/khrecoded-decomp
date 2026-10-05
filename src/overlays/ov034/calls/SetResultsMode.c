#include "nitro/types.h"

extern u32 data_ov034_020c0fa0[2];
#define resultsWork ((int)data_ov034_020c0fa0[1])

void SetResultsMode(u32 mode)

{
  *(u32 *)(resultsWork + 0x6bc8) = mode;
  *(u32 *)(resultsWork + 0x6bb0) = 0;
  return;
}
