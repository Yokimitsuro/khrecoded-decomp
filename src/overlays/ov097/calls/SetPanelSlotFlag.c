#include "nitro/types.h"

typedef struct {
    u8 data[0x6434];
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

extern void IndexedRecords_SetFlag2(int *base, int index, int value);

void SetPanelSlotFlag(int listIndex, int slotIndex, BOOL enabled, MenuScene *scene)
{
    PanelSlot *slot;

    if (listIndex == 1) {
        slot = &scene->subSlots[slotIndex];
    } else {
        slot = &scene->mainSlots[slotIndex];
    }
    IndexedRecords_SetFlag2((int *)&scene->panelLists[listIndex], slot->panelIndex, enabled);
}
