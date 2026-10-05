#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x30];
    u8 *object;
    u8 pad_34[0x58];
} PanelRecord;

typedef struct {
    u8 pad_0000[0x18];
    PanelRecord records[(0x6434 - 0x18) / 0x8c];
    u8 pad_tail[0x6434 - 0x18 - ((0x6434 - 0x18) / 0x8c) * 0x8c];
} PanelList;

typedef struct {
    int panelIndex;
    u8 pad_04[0x18];
} PanelSlot;

typedef struct {
    u8 pad_0000[0x218];
    PanelList panelLists[2];
    PanelSlot mainSlots[11];
    PanelSlot subSlots[1];
} MenuScene;

void *GetPanelSlotRecordData(int listIndex, int slotIndex, MenuScene *scene)
{
    PanelList *list = &scene->panelLists[listIndex];
    PanelSlot *slot;
    PanelRecord *record;
    u8 *object;

    if (listIndex == 1) {
        slot = &scene->subSlots[slotIndex];
    } else {
        slot = &scene->mainSlots[slotIndex];
    }
    if (slot->panelIndex < 0) {
        return NULL;
    }
    record = &list->records[slot->panelIndex];
    if (record == NULL) {
        return NULL;
    }
    object = record->object;
    if (object == NULL) {
        return NULL;
    }
    return object + 8 != NULL ? object + 8 : NULL;
}
