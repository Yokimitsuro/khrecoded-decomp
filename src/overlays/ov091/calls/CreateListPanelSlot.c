#include "nitro/types.h"

typedef struct {
    int resourceId;
    int animId;
    int x;
    int y;
    int flag;
    BOOL visible;
} PanelDesc;

typedef struct {
    int slotIndex;
    int x;
    int y;
    u8 pad_0c[0x8];
} ListPanel;

typedef struct {
    u8 pad_00[0xf4];
    u8 screenObjects[2][0x6434];
    ListPanel topPanels[6];
    ListPanel bottomPanels[6];
} MenuScene;

extern int PXI_Init_0204f0c8(void *objManager, int resourceId, int animId);
extern void func_0204f218(void *objManager, int slotIndex, int value);
extern void IndexedRecord_ClearActive(void *objManager, int slotIndex);
extern void func_0204f18c(void *objManager, int slotIndex, int scale);
extern void Slot_SetMode2Bit(void *objManager, int slotIndex, int value);
extern void IndexedRecords_SetFlag2(void *objManager, int slotIndex, int value);
extern int IndexedRecord_SetActive(void *objManager, int slotIndex);
extern void SetListPanelSlotPos(int screen, int panelIndex, int x, int y, MenuScene *scene);

void CreateListPanelSlot(int screen, int panelIndex, PanelDesc *desc, MenuScene *scene)
{
    u8 *objects = scene->screenObjects[screen];
    ListPanel *panel = screen == 0 ? &scene->topPanels[panelIndex] : &scene->bottomPanels[panelIndex];
    int slot = PXI_Init_0204f0c8(objects, desc->resourceId, desc->animId);

    func_0204f218(objects, slot, 0);
    IndexedRecord_ClearActive(objects, slot);
    func_0204f18c(objects, slot, 0);
    Slot_SetMode2Bit(objects, slot, 0);
    IndexedRecords_SetFlag2(objects, slot, desc->flag);
    if (desc->visible) {
        IndexedRecord_SetActive(objects, slot);
    }
    panel->slotIndex = slot;
    panel->x = desc->x;
    panel->y = desc->y;
    SetListPanelSlotPos(screen, panelIndex, desc->x, desc->y, scene);
}
