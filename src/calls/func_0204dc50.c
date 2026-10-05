#include "nitro/types.h"

extern unsigned int gSoundWork;

BOOL func_0204dc50(u32 handle) {
  int soundSlot;

  soundSlot = gSoundWork + 0xb4518 + (handle >> 0x18) * 0x20;
  if ((*(unsigned short *)(soundSlot + 0x14) != 0) && (*(u32 *)(soundSlot + 0x18) == (handle & 0xffffff))) {
    return *(int *)(soundSlot + 0x1c) != 0;
  }
  return FALSE;
}
