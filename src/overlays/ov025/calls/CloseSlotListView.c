#include "nitro/types.h"

typedef struct SlotRecord {
    u8 pad_00[4];
    u16 id;
} SlotRecord;

typedef struct ListOverlayCell {
    int cellIndex;
    int unk_4;
    int x;
    int y;
} ListOverlayCell;

typedef struct ListView {
    u8 pad_00[4];
    u16 *paramWord;
    u8 pad_08[0x68];
    SlotRecord *slots[3];
    u8 pad_7c[4];
    void *entryStates;
    void *workBuffer;
    void *cellSet;
    u8 pad_8c[0x14];
    int busy;
    u8 pad_a4[8];
    int overlayCellCount;
    ListOverlayCell overlayCells[1];
} ListView;

extern void func_0204f0d4(void *cellSet, int cellIndex);
extern void StoreSelectionPackedValues(u16 *values);
extern void SetParamWord8(int value);
extern void NNSi_FndFreeFromDefaultHeap(void *block);

void CloseSlotListView(ListView *list)
{
    u16 slotIds[3];
    int i;

    for (i = 0; i < 3; i++) {
        if (list->slots[i] == NULL) {
            break;
        }
        slotIds[i] = list->slots[i]->id;
    }
    for (; i < 3; i++) {
        slotIds[i] = 0xffff;
    }
    for (i = 0; i < list->overlayCellCount; i++) {
        func_0204f0d4(list->cellSet, list->overlayCells[i].cellIndex);
    }
    if (list->busy == 0) {
        StoreSelectionPackedValues(slotIds);
        SetParamWord8(*list->paramWord);
    }
    NNSi_FndFreeFromDefaultHeap(list->entryStates);
    NNSi_FndFreeFromDefaultHeap(list->workBuffer);
}
