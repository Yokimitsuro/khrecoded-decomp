#include "nitro/types.h"

typedef struct ObjManager {
  u8 data[0x6434];
} ObjManager;

typedef struct ObjPos {
  int x;
  int y;
} ObjPos;

typedef struct SlotEntry {
  int objIndex;
  ObjPos pos;
  u8 pad_0c[0x8];
} SlotEntry;

typedef struct SceneWork {
  u8 pad_000[0x45c];
  ObjManager objManagers[2];
  SlotEntry topSlots[21];
  SlotEntry bottomSlots[21];
} SceneWork;

extern void IndexedRecord_SetPair(ObjManager *manager, int objIndex, ObjPos *pos);

#define INT_TO_FX32(v) ((int)((float)(v) > 0.0f ? 0.5f + 4096.0f * (float)(v) : 4096.0f * (float)(v) - 0.5f))

void SetSlotObjPosition(int screen, int slot, int posX, int posY, SceneWork *work) {
  ObjManager *manager;
  SlotEntry *entry;
  ObjPos pos;

  manager = &work->objManagers[screen];
  if (screen == 0) {
    entry = &work->topSlots[slot];
  } else {
    entry = &work->bottomSlots[slot];
  }
  entry->pos.x = posX;
  entry->pos.y = posY;
  pos.x = INT_TO_FX32(entry->pos.x);
  pos.y = INT_TO_FX32(entry->pos.y);
  IndexedRecord_SetPair(manager, entry->objIndex, &pos);
}
