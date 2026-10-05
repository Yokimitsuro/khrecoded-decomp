#include "nitro/types.h"

extern u32 camera_commit_projection();
extern u32 func_01ffb12c();
extern u32 AdvanceAnimationTracks();
extern u32 AdvanceObjectAnimationTracks();
extern u32 DrawModelWithAttachment();
extern u32 func_ov074_020c5128();
extern u32 DrawRootMenuText();

void UpdateRootMenuGraphics(int context)

{
  if (*(u8 *)(context + 2) != '\0') {
    func_ov074_020c5128(context);
    DrawRootMenuText(context);
    *(u8 *)(context + 2) = *(u8 *)(context + 2) + -1;
  }
  if (*(int *)(context + 8) == 0) {
    return;
  }
  camera_commit_projection(context + 0x400);
  AdvanceAnimationTracks(context + 0x1c,0x1000);
  func_01ffb12c(context + 0x1c);
  if (*(int *)(context + 0xc) == 0) {
    return;
  }
  AdvanceObjectAnimationTracks(context + 0x120,0x1000);
  DrawModelWithAttachment(context + 0x120);
  return;
}
