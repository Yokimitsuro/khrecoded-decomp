#include "nitro/types.h"

extern u32 VEC_Add();

void AddObjectOffsetVector(int object,void *offset)

{
  if ((object != 0) && (offset != (void *)0x0)) {
    VEC_Add((void *)(object + 0x374),offset,(void *)(object + 0x374));
  }
  return;
}
