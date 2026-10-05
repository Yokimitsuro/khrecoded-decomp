#include "nitro/types.h"

extern void MI_CpuFill8(void *dst, int value, int size);
extern void G3X_SetHOffset(int value);
extern void LoadViewerModelTable(u8 *viewer);
extern void InitModelCamera(u8 *viewer);
extern void func_ov099_020c2078(u8 *viewer, int selection);

void ResetModelViewer(u8 *viewer) {
  MI_CpuFill8(viewer, 0, 0x5f8);
  *(int *)(viewer + 0x5bc) = -1;
  G3X_SetHOffset(-0x44);
  LoadViewerModelTable(viewer);
  InitModelCamera(viewer);
  func_ov099_020c2078(viewer, 0);
}
