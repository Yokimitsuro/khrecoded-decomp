#include "nitro/types.h"

extern u32 func_01ffb12c();

void DrawNodeAtInvertedY(void *node,u32 x,int y)

{
  *(u32 *)((int)node + 0xa4) = x;
  *(int *)((int)node + 0xa8) = 0xc0000 - y;
  func_01ffb12c(node);
  return;
}
