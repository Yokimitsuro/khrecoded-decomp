#include "nitro/types.h"

extern u32 PlaySoundEffect();
extern u32 StartSubScene();
extern u32 func_ov039_020bca20();
extern u32 GetDialogInputMode();

void TryOpenMatrixMenuThree(int context)

{
  int result;
  
  if ((((((*(int *)(context + 0x78) != 0) && (*(int *)(context + 0x12dc8) == 0)) &&
        (*(int *)(context + 0x74) == 0)) &&
       ((*(int *)(context + 0x17524) == 0 && (*(int *)(context + 0x88) == 0)))) &&
      ((*(int *)(context + 0x13ea0) == 0 &&
       ((*(u16 *)(context + 0x13e64) == 0 && (result = GetDialogInputMode(context), result == 0)))))) &&
     (result = func_ov039_020bca20(), (*(u16 *)(result + 8) & 3) == 0)) {
    PlaySoundEffect(1,2);
    StartSubScene(3,0xffffffff,0);
  }
  return;
}
