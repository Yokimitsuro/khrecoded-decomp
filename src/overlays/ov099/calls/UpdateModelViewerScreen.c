#include "nitro/types.h"

typedef void (*ModeHandler)(u8 *work);

extern const ModeHandler gEnemyReportStateHandlers[];
extern int func_ov099_020c1798(u8 *work);
extern void func_ov099_020c081c(u8 *work);
extern void DrawModelViewer(u8 *viewer);

void UpdateModelViewerScreen(u8 *work) {
  int mode = func_ov099_020c1798(work);

  if (gEnemyReportStateHandlers[mode] != NULL) {
    gEnemyReportStateHandlers[mode](work);
  }
  if (++*(int *)(work + 0xd6e4) >= 0x3c) {
    *(int *)(work + 0xd6e4) = 0;
    *(int *)(work + 0xd6e8) = (*(int *)(work + 0xd6e8) + 1) % 2;
  }
  func_ov099_020c081c(work);
  DrawModelViewer(work + 0xd0ec);
}
