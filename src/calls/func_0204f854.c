#include "nitro/types.h"

extern u32 data_0205fe0c;
extern u32 ComputePlayerStats();
extern u32 GetOverlaySelectionRecord();

void func_0204f854(void) {
  void *out;

  out = GetOverlaySelectionRecord(0);
  ComputePlayerStats(data_0205fe0c,out,0,1);
}
