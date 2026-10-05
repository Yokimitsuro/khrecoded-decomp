#include "nitro/types.h"

extern struct { int reserved; int context; } data_ov001_020a04c4;
#define activeManager data_ov001_020a04c4.context
extern u32 FillBackgroundLayerRect();
extern u32 FlushBufferAndRunCallback();
extern u32 SelectListNodeOrFirst();
extern u32 func_ov027_020b9e10();
extern u32 GetPanelLayerScreen();
extern u32 func_ov001_0207123c();
extern u32 func_ov027_020b9e20();

void DrawFieldMessageById(int messageId)

{
  int manager;
  int layerOwner;
  void *tileBuffer;
  int entryIndex;
  
  manager = activeManager;
  layerOwner = func_ov001_0207123c();
  tileBuffer = (void *)GetPanelLayerScreen(0xb);
  entryIndex = 0;
  do {
    if (messageId == *(int *)(manager + entryIndex * 8 + 0xe0)) {
      SelectListNodeOrFirst
                ((void *)(manager + 0xa8),*(void **)(manager + entryIndex * 8 + 0xdc));
      FlushBufferAndRunCallback((void *)(manager + 0xa8));
      break;
    }
    entryIndex = entryIndex + 1;
  } while (entryIndex < 0x16);
  if (entryIndex < 0x16) {
    if (tileBuffer == (void *)0x0) {
      tileBuffer = (void *)func_ov027_020b9e10(layerOwner,0xb);
      FillBackgroundLayerRect((void *)(manager + 0xa8),tileBuffer,0x16,0,'\x0f');
      func_ov027_020b9e20(layerOwner,0xb);
      return;
    }
    FillBackgroundLayerRect((void *)(manager + 0xa8),tileBuffer,0x16,0,'\x0f');
  }
  return;
}
