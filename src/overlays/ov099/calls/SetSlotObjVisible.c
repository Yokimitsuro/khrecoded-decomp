#include "nitro/types.h"

typedef struct {
    u8 data[0x6434];
} ObjManager;

typedef struct {
    int objIndex;
    int posY;
    u8 pad_08[0xc];
} SlotEntry;

typedef struct {
    u8 pad_000[0x45c];
    ObjManager objManagers[2];
    SlotEntry topSlots[21];
    SlotEntry bottomSlots[21];
} SceneWork;

extern void IndexedRecords_SetFlag2(int *base, int index, int value);

void SetSlotObjVisible(int screen, int slot, int visible, SceneWork *work)
{
    SlotEntry *entry;

    if (screen == 0) {
        entry = &work->topSlots[slot];
    } else {
        entry = &work->bottomSlots[slot];
    }
    IndexedRecords_SetFlag2((int *)&work->objManagers[screen], entry->objIndex, visible);
}
