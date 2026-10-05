#include "nitro/types.h"

typedef struct SlotRecord {
    u8 pad_00[4];
    u16 id;
} SlotRecord;

typedef struct ListOverlayCell {
    int cellIndex;
    u8 pad_04[0xc];
} ListOverlayCell;

typedef struct ListView {
    u8 pad_00[4];
    u16 *data;
    u8 pad_08[0x70 - 0x08];
    SlotRecord *slots[3];
    u8 pad_7c[4];
    void *buffer0;
    void *buffer1;
    void *cellSet;
    u8 pad_8c[0xa0 - 0x8c];
    BOOL cancelled;
    u8 pad_a4[0xac - 0xa4];
    int overlayCellCount;
    ListOverlayCell overlayCells[1];
} ListView;

extern void func_0204f0d4(void *cellSet, int cellIndex);
extern void StoreSelectionPackedValues(u16 *values);
extern void SetParamWord8(int value);
extern void NNSi_FndFreeFromDefaultHeap(void *block);

void ReleaseListView(ListView *list)
{
    u16 ids[4];
    int i;

    for (i = 0; i < 3; i++) {
        if (list->slots[i] == NULL) {
            break;
        }
        ids[i] = list->slots[i]->id;
    }
    for (; i < 3; i++) {
        ids[i] = 0xffff;
    }
    for (i = 0; i < list->overlayCellCount; i++) {
        func_0204f0d4(list->cellSet, list->overlayCells[i].cellIndex);
    }
    if (!list->cancelled) {
        StoreSelectionPackedValues(ids);
        SetParamWord8(*list->data);
    }
    NNSi_FndFreeFromDefaultHeap(list->buffer0);
    NNSi_FndFreeFromDefaultHeap(list->buffer1);
}
