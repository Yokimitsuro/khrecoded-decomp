#include "nitro/types.h"

extern u32 Text_UploadTileBuffer();

void UploadDirtySubtitleTiles(void *stream)

{
  if (*(int *)((int)stream + 0x44) == 0) {
    return;
  }
  Text_UploadTileBuffer(stream);
  *(u32 *)((int)stream + 0x44) = 0;
  return;
}
