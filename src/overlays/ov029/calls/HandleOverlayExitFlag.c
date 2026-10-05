#include "nitro/types.h"

extern u16 data_02060500;
extern u32 data_ov029_020babc0;
extern u32 func_ov001_0206dc4c();
extern u32 func_ov001_0206e444();

u32 HandleOverlayExitFlag(void)

{
  int state;
  
  state = data_ov029_020babc0;
  if ((data_02060500 & 0x400) != 0) {
    func_ov001_0206dc4c(0);
  }
  if ((*(u16 *)(state + 6) & 0x4000) != 0) {
    func_ov001_0206e444(1);
    *(u16 *)(data_ov029_020babc0 + 6) = *(u16 *)(data_ov029_020babc0 + 6) | 0x8000;
    return 6;
  }
  return 0xffffffff;
}
