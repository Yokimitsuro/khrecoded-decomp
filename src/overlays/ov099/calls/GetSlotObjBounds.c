#include "nitro/types.h"

typedef struct {
    s16 maxX;
    s16 maxY;
    s16 minX;
    s16 minY;
} ObjBounds;

typedef struct {
    u8 pad_00[8];
    ObjBounds bounds;
} ObjCell;

typedef struct {
    u8 pad_00[0x30];
    ObjCell *cell;
    u8 pad_34[0x8c - 0x34];
} ObjEntry;

typedef struct {
    u8 pad_0000[0x18];
    ObjEntry objs[182];
    u8 pad_63a0[0x6434 - 0x63a0];
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

ObjBounds *GetSlotObjBounds(int screen, int slot, SceneWork *work)
{
    ObjManager *manager;
    SlotEntry *entry;
    ObjEntry *obj;
    ObjBounds *bounds;

    manager = &work->objManagers[screen];
    if (screen == 0) {
        entry = &work->topSlots[slot];
    } else {
        entry = &work->bottomSlots[slot];
    }
    if (entry->objIndex < 0) {
        return NULL;
    }
    obj = &manager->objs[entry->objIndex];
    if (obj == NULL) {
        return NULL;
    }
    if (obj->cell == NULL) {
        return NULL;
    }
    bounds = &obj->cell->bounds;
    if (bounds == NULL) {
        return NULL;
    }
    return bounds;
}
