#include "nitro/types.h"

extern u32 data_ov034_020c0fa0[2];
#define resultsWork ((int)data_ov034_020c0fa0[1])

u32 ClassifyResultsShopEntry(int itemIndex)

{
  int reservedCount;
  
  if (0 < *(int *)(resultsWork + 0x6d6c)) {
    reservedCount = 2;
    if (*(int *)(resultsWork + 0x6d70) <= 0) {
      reservedCount = 1;
    }
    if (itemIndex == *(int *)(resultsWork + 0x6d64) - reservedCount) {
      return 2;
    }
  }
  if ((0 < *(int *)(resultsWork + 0x6d70)) && (itemIndex == *(int *)(resultsWork + 0x6d64) + -1)) {
    return 1;
  }
  return 0;
}
