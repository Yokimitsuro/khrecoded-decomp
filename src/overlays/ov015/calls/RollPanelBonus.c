#include "nitro/types.h"

#define false 0
#define true 1
extern u32 func_0202a9e4();
extern u32 DispatchContextCommand();

BOOL RollPanelBonus(void)

{
  u32 roll;
  int count;
  int blocked;
  
  roll = func_0202a9e4(100);
  count = DispatchContextCommand(8,0,0,0);
  blocked = DispatchContextCommand(5,0,0,0);
  if (blocked != 0) {
    return false;
  }
  if ((count >= 0x50) && ((int)roll < 0x18)) {
    return true;
  }
  if ((count >= 0x32) && ((int)roll < 6)) {
    return true;
  }
  return (int)roll < 1;
}
