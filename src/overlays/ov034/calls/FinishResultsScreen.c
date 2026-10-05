#include "nitro/types.h"

extern u32 data_ov034_020c0fa0[2];
#define resultsWork ((int)data_ov034_020c0fa0[1])
typedef struct SystemFlags { u8 pad[6]; u16 mode : 3; u16 rest : 13; } SystemFlags;
extern SystemFlags data_0206085c;
#define systemFlags data_0206085c.mode
extern u32 SetPanelEnabled();
extern u32 StoreToGlobalPtr4Field28();
extern u32 ReleaseSeqArcHeapLevel();
extern u32 func_ov034_020bce10();

u32 FinishResultsScreen(void)

{
  func_ov034_020bce10();
  SetPanelEnabled(1);
  if ((*(int *)(resultsWork + 0x6d90) != 1) || (systemFlags != 1)) {
    ReleaseSeqArcHeapLevel(1);
  }
  StoreToGlobalPtr4Field28(1);
  *(u16 *)(resultsWork + 6) = *(u16 *)(resultsWork + 6) | 0x8000;
  return 3;
}
