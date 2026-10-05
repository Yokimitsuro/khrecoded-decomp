#include "nitro/types.h"

void GetWidgetTileDimensions(int widget,u32 *widthOut,u32 *heightOut)

{
  u32 dimension;
  
  dimension = (u32)((u32)**(u16 **)(*(int *)(widget + 0x18) + 8) >> 3);
  if ((int)*(short *)(widget + 10) != 0xffffffff) {
    dimension = (int)*(short *)(widget + 10);
  }
  *widthOut = dimension;
  dimension = (u32)*(short *)(widget + 0xc);
  if (dimension == 0xffffffff) {
    dimension = (u32)((u32)*(u16 *)(*(int *)(*(int *)(widget + 0x18) + 8) + 2) >> 3);
  }
  *heightOut = dimension;
  return;
}
