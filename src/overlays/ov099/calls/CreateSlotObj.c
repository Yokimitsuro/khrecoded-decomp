#include "nitro/types.h"

typedef struct ObjManager {
  u8 data[0x6434];
} ObjManager;

typedef struct SlotEntry {
  int objIndex;
  int posX;
  int posY;
  int width;
  int height;
} SlotEntry;

typedef struct SceneWork {
  u8 pad_000[0x45c];
  ObjManager objManagers[2];
  SlotEntry topSlots[21];
  SlotEntry bottomSlots[21];
} SceneWork;

typedef struct SlotObjDesc {
  int resource;
  int cell;
  int posX;
  int posY;
  int priority;
  int hidden;
} SlotObjDesc;

typedef struct ObjBounds {
  s16 maxX;
  s16 maxY;
  s16 minX;
  s16 minY;
} ObjBounds;

extern int PXI_Init_0204f0c8(ObjManager *manager, int resource, int cell);
extern void func_0204f218(ObjManager *manager, int objIndex, int value);
extern void IndexedRecord_ClearActive(ObjManager *manager, int objIndex);
extern void Slot_SetMode2Bit(ObjManager *manager, int objIndex, int value);
extern void IndexedRecords_SetFlag2(ObjManager *manager, int objIndex, int value);
extern void IndexedRecord_SetActive(ObjManager *manager, int objIndex);
extern void SetSlotObjPosition(int screen, int slot, int posX, int posY, SceneWork *work);
extern ObjBounds *GetSlotObjBounds(int screen, int slot, SceneWork *work);

void CreateSlotObj(int screen, int slot, SlotObjDesc *desc, SceneWork *work) {
  ObjManager *manager;
  SlotEntry *entry;
  int objIndex;
  ObjBounds *bounds;

  manager = &work->objManagers[screen];
  if (screen == 0) {
    entry = &work->topSlots[slot];
  } else {
    entry = &work->bottomSlots[slot];
  }
  objIndex = PXI_Init_0204f0c8(manager, desc->resource, desc->cell);
  func_0204f218(manager, objIndex, 0);
  IndexedRecord_ClearActive(manager, objIndex);
  Slot_SetMode2Bit(manager, objIndex, 0);
  IndexedRecords_SetFlag2(manager, objIndex, desc->priority);
  if (desc->hidden != 0) {
    IndexedRecord_SetActive(manager, objIndex);
  }
  entry->objIndex = objIndex;
  entry->posX = desc->posX;
  entry->posY = desc->posY;
  SetSlotObjPosition(screen, slot, desc->posX, desc->posY, work);
  bounds = GetSlotObjBounds(screen, slot, work);
  entry->width = bounds->maxX - bounds->minX + 1;
  entry->height = bounds->maxY - bounds->minY + 1;
}
