#include "nitro/types.h"

void GetDialogPixelBounds(int context,int *bottom,int *left,int *right)

{
  int centerTile;
  
  centerTile = (int)*(short *)(context + 0x9c0c) + ((u32)*(u16 *)(context + 0x9c10) >> 1);
  *left = (centerTile + -7) * 8;
  *bottom = ((int)*(short *)(context + 0x9c0e) + (u32)*(u16 *)(context + 0x9c12) + -2) * 8;
  *right = (centerTile + 7) * 8;
  return;
}
