#include "nitro/types.h"

extern u32 CallVirtualHandlerSlot1();

void ResetSubtitleLine(void *stream)

{
  *(u32 *)((int)stream + 0x60) = 0;
  *(u32 *)((int)stream + 0x50) = 0;
  *(u32 *)((int)stream + 0x44) = 1;
  CallVirtualHandlerSlot1(stream,0);
  return;
}
