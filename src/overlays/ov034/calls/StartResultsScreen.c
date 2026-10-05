#include "nitro/types.h"

extern u32 data_ov034_020c0fa0[2];
#define resultsWork ((int)data_ov034_020c0fa0[1])
extern u32 SetPanelEnabled();
extern u32 func_ov001_02063620();
extern u32 func_ov034_020bb324();

u32 StartResultsScreen(void)

{
  u16 statusFlags;
  int work;
  int status;
  
  work = resultsWork;
  status = func_ov001_02063620();
  if (status != 0) {
    return 0xffffffff;
  }
  SetPanelEnabled(0);
  func_ov034_020bb324();
  statusFlags = *(u16 *)(work + 6);
  if ((statusFlags & 1) != 0) {
    *(u16 *)(work + 6) = statusFlags & 0xfffe;
  }
  *(u16 *)(resultsWork + 6) = *(u16 *)(resultsWork + 6) | 0x8000;
  return 1;
}
