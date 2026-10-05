#include "nitro/types.h"

typedef struct HandleBuffer {
  u8 data[0xc];
} HandleBuffer;

typedef struct ObjectList {
  u8 data[0x34];
} ObjectList;

extern void CallVirtualHandlerSlot1(void *object, int arg);
extern void FlushBufferAndRunCallback(void *object);
extern void DestroyFndObjectList(void *object);
extern void FreePointerIfSet(void *slot);
extern void FreeResourceBufferAndProbeHeap(void *buffer);

void FreeViewerResources(u8 *work) {
  int index;
  int slot;

  for (index = 0; index < 4; index++) {
    CallVirtualHandlerSlot1((ObjectList *)(work + 0x31c) + index, 0);
    FlushBufferAndRunCallback((ObjectList *)(work + 0x31c) + index);
    DestroyFndObjectList((ObjectList *)(work + 0x31c) + index);
  }
  FreePointerIfSet(work + 0xcef8);
  for (slot = 0; slot < 2; slot++) {
    FreePointerIfSet((HandleBuffer *)(work + 0xcee0) + slot);
  }
  FreeResourceBufferAndProbeHeap(work + 0x310);
}
