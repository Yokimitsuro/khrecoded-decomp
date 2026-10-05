#include "nitro/types.h"

extern u32 GXx_GetMasterBrightness_();
extern u32 SetSceneMode();

void RequestEntryTransitionIfIdle(u32 context)

{
  int result;
  
  result = GXx_GetMasterBrightness_(0x400006c);
  if (result != 0) {
    return;
  }
  SetSceneMode(2,context);
  return;
}
