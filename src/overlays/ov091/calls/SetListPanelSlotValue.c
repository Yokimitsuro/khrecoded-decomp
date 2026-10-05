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

extern void IndexedRecord_ClearActive(void *objManager, int slotIndex);
extern void func_0204f218(void *objManager, int slotIndex, u16 value);

void SetListPanelSlotValue(int screen, int panelIndex, int value, MenuScene *scene)
{
    u8 *objects = scene->screenObjects[screen];
    ListPanel *panel = screen == 0 ? &scene->topPanels[panelIndex] : &scene->bottomPanels[panelIndex];

    IndexedRecord_ClearActive(objects, panel->slotIndex);
    func_0204f218(objects, panel->slotIndex, value);
}
