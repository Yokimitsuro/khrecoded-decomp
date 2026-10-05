#include "nitro/types.h"

extern u32 FX_Mul();
extern u32 NNS_G3dMdlSetMdlAlphaAll();
extern u32 func_ov021_020ab85c();

void UpdateModelFadeAlpha(int object,int delta)

{
  int alpha;
  
  if ((*(char *)(object + 0x131) != '\0') && (*(char *)(object + 0x131) == '\x01')) {
    alpha = FX_Mul(delta,0x1b00);
    alpha = *(int *)(object + 0x144) - alpha;
    *(int *)(object + 0x144) = alpha;
    if (alpha <= 0) {
      func_ov021_020ab85c(object);
    }
    NNS_G3dMdlSetMdlAlphaAll
              (*(void **)(object + 0x78),*(int *)(object + 0x144) >> 0xc);
  }
  return;
}
