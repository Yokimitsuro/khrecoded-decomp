#include "nitro/types.h"

extern u32 func_ov001_02063838();
extern u32 GetManagerStateFlag();
extern u32 SnapshotActorSlotPositions();

void func_020284e4(void) {
  int active;

  active = func_ov001_02063838();
  if (active != 0) {
    GetManagerStateFlag();
    return;
  }
  SnapshotActorSlotPositions();
}
