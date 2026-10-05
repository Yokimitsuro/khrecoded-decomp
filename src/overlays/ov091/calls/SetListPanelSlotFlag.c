#include "nitro/types.h"

typedef struct {
    int slotIndex;
    u8 pad_04[0x10];
} ListPanel;

typedef struct {
    u8 pad_00[0xf4];
    u8 screenObjects[2][0x6434];
    ListPanel topPanels[6];
    ListPanel bottomPanels[6];
} MenuScene;

extern void IndexedRecords_SetFlag2(int *objManager, int slotIndex, int value);

void SetListPanelSlotFlag(int screen, int panelIndex, int value, MenuScene *scene)
{
    ListPanel *panel = screen == 0 ? &scene->topPanels[panelIndex] : &scene->bottomPanels[panelIndex];

    IndexedRecords_SetFlag2((int *)scene->screenObjects[screen], panel->slotIndex, value);
}
