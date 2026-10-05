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

extern void func_0204f0d4(void *objManager, int slotIndex);

void ReleaseListRecords(MenuScene *scene)
{
    ListPanel *panel;
    int i;

    for (i = 0; i < 6; i++) {
        panel = &scene->topPanels[i];
        if (panel->slotIndex != -1) {
            func_0204f0d4(scene->screenObjects[0], panel->slotIndex);
            panel->slotIndex = -1;
        }
    }
    panel = &scene->bottomPanels[0];
    if (panel->slotIndex != -1) {
        func_0204f0d4(scene->screenObjects[1], panel->slotIndex);
        panel->slotIndex = -1;
    }
}
