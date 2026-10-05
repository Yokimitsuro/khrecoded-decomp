#include "nitro/types.h"

#define false 0
#define true 1
extern u8 data_ov075_020d1474[];

u8 * GetMatrixModeLabel(int mode)

{
  if ((mode < 3) || (mode >= 14)) {
    mode = 0;
  }
  else {
    mode = mode + -2;
  }
  return data_ov075_020d1474 + mode * 4;
}
