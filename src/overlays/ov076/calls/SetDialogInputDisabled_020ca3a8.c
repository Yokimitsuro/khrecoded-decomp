#include "nitro/types.h"

void SetDialogInputDisabled_020ca3a8(int context,int value)

{
  *(u8 *)(context + 0xc) = value == 0;
  return;
}
