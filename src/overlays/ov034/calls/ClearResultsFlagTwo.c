#include "nitro/types.h"

extern u32 data_ov034_020c0fa0[2];
#define resultsWork ((int)data_ov034_020c0fa0[1])

void ClearResultsFlagTwo(void)

{
  *(u16 *)(resultsWork + 6) = *(u16 *)(resultsWork + 6) & 0xfffd;
  return;
}
