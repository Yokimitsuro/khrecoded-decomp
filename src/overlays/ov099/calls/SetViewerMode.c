#include "nitro/types.h"

void SetViewerMode(u32 mode, u8 *work) {
  *(u32 *)(work + 0xd6ec) = mode;
  *(u32 *)(work + 0xd6f0) = 0;
  *(u32 *)(work + 0xd6f4) = 0;
}
