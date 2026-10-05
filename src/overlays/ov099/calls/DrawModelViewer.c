#include "nitro/types.h"

extern void camera_commit_projection(void *camera);
extern void AdvanceAnimationTracks(void *model, int step);
extern void func_ov099_020c1908(void *model);
extern void func_01ffb12c(void *model);

void DrawModelViewer(u8 *viewer) {
  int index;
  u8 *model;

  camera_commit_projection(viewer + 0x5c0);
  index = 0;
  if (**(int **)(viewer + *(int *)(viewer + 0x5bc) * 4 + 4) <= 0) {
    return;
  }
  do {
    model = viewer + 0xa8 + index * 0x104;
    AdvanceAnimationTracks(model, 0x1000);
    if (*(int *)(viewer + 0x5bc) == 0x21 || *(int *)(viewer + 0x5bc) == 1) {
      func_ov099_020c1908(model);
    } else {
      func_01ffb12c(model);
    }
    index++;
  } while (index < **(int **)(viewer + *(int *)(viewer + 0x5bc) * 4 + 4));
}
