#include "nitro/types.h"

extern void LoadDefaultProjectionValues(void *projection);

void InitModelCamera(u8 *viewer) {
  LoadDefaultProjectionValues(viewer + 0x5c0);
  *(u32 *)(viewer + 0x5e8) = 0x3000;
  *(u32 *)(viewer + 0x5e4) = 0x1000;
  *(u32 *)(viewer + 0x5d8) = 0x1000;
}
