#include "nitro/types.h"

extern int data_ov032_020c0088[];
#define activeContext_020c006c data_ov032_020c0088[1]
extern u32 _s32_div_f();

void SetGroupMenuProgress(int percent)

{
  int menu;
  int targetCount;
  
  menu = activeContext_020c006c;
  if (activeContext_020c006c != 0) {
    if (0 < percent) {
      targetCount = _s32_div_f(percent * 0x57,100);
      *(int *)(menu + 0x24) = targetCount;
      return;
    }
    *(u32 *)(activeContext_020c006c + 0x24) = 0;
  }
  return;
}
