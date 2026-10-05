#include "nitro/types.h"

void SetMatrixInputDisabled(int context,int value)

{
  *(u8 *)(context + 0x13e7c) = value == 0;
  return;
}
