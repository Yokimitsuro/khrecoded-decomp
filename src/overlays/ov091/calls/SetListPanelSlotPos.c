#include "nitro/types.h"
#include "nitro/fx_types.h"

#define INT_TO_FX32(n) ((fx32)(((f32)(n) > 0) ? ((f32)(n) * 4096.0f + 0.5f) : ((f32)(n) * 4096.0f - 0.5f)))

typedef float f32;

typedef struct {
    int slotIndex;
    int x;
    int y;
    u8 pad_0C[0x8];
} ListPanel;

typedef struct {
    u8 pad_00[0xf4];
    u8 screenObjects[2][0x6434];
    ListPanel topPanels[6];
    ListPanel bottomPanels[6];
} MenuScene;

typedef struct {
    fx32 x;
    fx32 y;
} SlotPos;

extern void IndexedRecord_SetPair(void *objManager, int slotIndex, SlotPos *pos);

void SetListPanelSlotPos(int screen, int panelIndex, int x, int y, MenuScene *scene)
{
    void *objects = scene->screenObjects[screen];
    ListPanel *panel = screen == 0 ? &scene->topPanels[panelIndex] : &scene->bottomPanels[panelIndex];
    SlotPos pos;

    panel->x = x;
    panel->y = y;
    pos.x = INT_TO_FX32(panel->x);
    pos.y = INT_TO_FX32(panel->y);
    IndexedRecord_SetPair(objects, panel->slotIndex, &pos);
}
