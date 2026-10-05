#include "nitro/types.h"

typedef struct ObjManager {
  u8 data[0x6434];
} ObjManager;

typedef struct SlotEntry {
  int objIndex;
  int posX;
  int posY;
  u8 pad_0c[0x8];
} SlotEntry;

typedef struct SceneWork {
  u8 pad_000[0x45c];
  ObjManager objManagers[2];
  SlotEntry topSlots[21];
  SlotEntry bottomSlots[21];
} SceneWork;

extern void IndexedRecord_ClearActive(ObjManager *manager, int objIndex);
extern void func_0204f218(ObjManager *manager, int objIndex, int value);

void RefreshSlotObj(int screen, int slot, u32 value, SceneWork *work) {
  ObjManager *manager;
  SlotEntry *entry;

  manager = &work->objManagers[screen];
  if (screen == 0) {
    entry = &work->topSlots[slot];
  } else {
    entry = &work->bottomSlots[slot];
  }
  IndexedRecord_ClearActive(manager, entry->objIndex);
  func_0204f218(manager, entry->objIndex, (u16)value);
}
