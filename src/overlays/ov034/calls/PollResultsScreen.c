#include "nitro/types.h"

extern u32 data_ov034_020c0fa0[2];
#define resultsWork ((int)data_ov034_020c0fa0[1])
extern u32 func_ov034_020bb598();

u32 PollResultsScreen(void)

{
  int result;
  u32 nextState;
  
  result = resultsWork;
  nextState = 0xffffffff;
  func_ov034_020bb598();
  if ((*(u16 *)(result + 6) & 0x4000) != 0) {
    nextState = 2;
  }
  return nextState;
}
