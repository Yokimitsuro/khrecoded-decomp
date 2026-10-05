#include "nitro/types.h"

typedef struct {
    u16 id;
    u16 pad_02;
    u8 used;
    u8 pad_05[0x7];
} SelectionSlot;

typedef struct {
    SelectionSlot slots[21];
    u8 pad_fc[0x4];
    s32 slotCount;
    s16 cursor;
} SelectionList;

typedef struct {
    u8 pad_00[0x2c];
    SelectionList list;
} OverlaySelectionRecord;

extern OverlaySelectionRecord *GetOverlaySelectionRecord(u32 selectionIndex);

void ResetSelectionSlots(void)
{
    int i = 0;
    SelectionList *list = &GetOverlaySelectionRecord(0)->list;

    list->slotCount = 0;
    do {
        list->slots[i].id = i + 0xdd;
        list->slots[i].used = 0;
        list->slotCount++;
        i++;
    } while (i < 4);
    list->cursor = -1;
}
