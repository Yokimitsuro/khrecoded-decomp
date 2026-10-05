#include "nitro/types.h"

void SetDialogInputDisabled_020c73dc(int context,int value)

{
  *(u8 *)(context + 0xc) = value == 0;
  return;
}
