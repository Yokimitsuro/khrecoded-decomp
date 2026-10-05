#include "nitro/types.h"

typedef struct EnemyBitInfo {
  u32 id;
  u32 bitOffset;
} EnemyBitInfo;

extern EnemyBitInfo data_ov099_020c243c[];
extern u32 ReadGlobalPackedBits(u32 bitOffset, u32 bitCount);
extern BOOL IsGlobalPackedBitSet(int bitIndex);
extern void SetGlobalPackedBit(int bitIndex);
extern void func_ov099_020c16d4(int list, int index);

void SyncEnemyEntryFlags(void) {
  int index;

  for (index = 0; index < 0x28; index++) {
    if (ReadGlobalPackedBits(data_ov099_020c243c[index].bitOffset, 0x11) != 0) {
      func_ov099_020c16d4(0, index);
      SetGlobalPackedBit(index + 0x1172);
    }
    if (!IsGlobalPackedBitSet(index + 0x1222) && IsGlobalPackedBitSet(index + 0x1172)) {
      func_ov099_020c16d4(1, index);
    }
  }
}
