#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x30];
    u8 *resource;
    u8 pad_34[0x58];
} ObjSlot;

typedef struct {
    u8 pad_00[0x18];
    ObjSlot slots[1];
} ObjManager;

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

void *GetListPanelSlotData(int screen, int panelIndex, MenuScene *scene)
{
    ObjManager *objects = (ObjManager *)scene->screenObjects[screen];
    ListPanel *panel = screen == 0 ? &scene->topPanels[panelIndex] : &scene->bottomPanels[panelIndex];
    ObjSlot *slot;
    u8 *resource;

    if (panel->slotIndex < 0) {
        return NULL;
    }
    slot = &objects->slots[panel->slotIndex];
    if (slot == NULL) {
        return NULL;
    }
    resource = slot->resource;
    if (resource == NULL) {
        return NULL;
    }
    resource += 8;
    if (resource == NULL) {
        return NULL;
    }
    return resource;
}
