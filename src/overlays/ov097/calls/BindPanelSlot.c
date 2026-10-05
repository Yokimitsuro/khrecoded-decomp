#include "nitro/types.h"

typedef struct {
    u8 data[0x6434];
} PanelList;

typedef struct {
    s16 left;
    s16 top;
    s16 right;
    s16 bottom;
} PanelRect;

typedef struct {
    int panelIndex;
    int x;
    int y;
    int width;
    int height;
    PanelRect rect;
} PanelSlot;

typedef struct {
    u8 pad_0000[0x218];
    PanelList panelLists[2];
    PanelSlot mainSlots[11];
    PanelSlot subSlots[1];
} MenuScene;

typedef struct {
    int resourceA;
    int resourceB;
    int x;
    int y;
    int flag;
    BOOL highlighted;
    u32 scale;
} PanelSlotDesc;

extern int PXI_Init_0204f0c8(void *list, int resourceA, int resourceB);
extern void func_0204f218(void *list, int index, int frames);
extern void IndexedRecord_ClearActive(void *list, int index);
extern void Slot_SetMode2Bit(void *list, int index, int value);
extern void IndexedRecords_SetFlag2(void *list, int index, int value);
extern void func_0204f18c(void *list, int index, int scale);
extern int IndexedRecord_SetActive(void *list, int index);
extern void SetPanelSlotPosition(int listIndex, int slotIndex, int x, int y, MenuScene *scene);
extern PanelRect *GetPanelSlotRecordData(int listIndex, int slotIndex, MenuScene *scene);
extern void MI_CpuCopy8(const void *src, void *dst, u32 size);

void BindPanelSlot(int listIndex, int slotIndex, PanelSlotDesc *desc, MenuScene *scene)
{
    PanelList *list = &scene->panelLists[listIndex];
    PanelSlot *slot;
    PanelRect *rect;
    int panelIndex;

    if (listIndex == 1) {
        slot = &scene->subSlots[slotIndex];
    } else {
        slot = &scene->mainSlots[slotIndex];
    }
    panelIndex = PXI_Init_0204f0c8(list, desc->resourceA, desc->resourceB);
    func_0204f218(list, panelIndex, 0);
    IndexedRecord_ClearActive(list, panelIndex);
    Slot_SetMode2Bit(list, panelIndex, 0);
    IndexedRecords_SetFlag2(list, panelIndex, desc->flag);
    func_0204f18c(list, panelIndex, desc->scale & 0xff);
    if (desc->highlighted) {
        IndexedRecord_SetActive(list, panelIndex);
    }
    slot->panelIndex = panelIndex;
    slot->x = desc->x;
    slot->y = desc->y;
    SetPanelSlotPosition(listIndex, slotIndex, desc->x, desc->y, scene);
    rect = GetPanelSlotRecordData(listIndex, slotIndex, scene);
    slot->width = rect->left - rect->right + 1;
    slot->height = rect->top - rect->bottom + 1;
    MI_CpuCopy8(rect, &slot->rect, sizeof(PanelRect));
}
