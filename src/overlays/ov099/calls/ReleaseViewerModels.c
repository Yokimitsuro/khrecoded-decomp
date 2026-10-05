#include "nitro/types.h"

extern void ReleaseResourceAndDetach(void *model);
extern void NNS_GfdResetFrmTexVramState(void);
extern void NNS_GfdResetFrmPlttVramState(void);

void ReleaseViewerModels(u8 *viewer) {
  int index = 0;

  if (**(int **)(viewer + *(int *)(viewer + 0x5bc) * 4 + 4) > 0) {
    do {
      ReleaseResourceAndDetach(viewer + 0xa8 + index * 0x104);
      index++;
    } while (index < **(int **)(viewer + *(int *)(viewer + 0x5bc) * 4 + 4));
  }
  NNS_GfdResetFrmTexVramState();
  NNS_GfdResetFrmPlttVramState();
}
