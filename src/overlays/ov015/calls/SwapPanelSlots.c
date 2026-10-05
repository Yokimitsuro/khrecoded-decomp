#include "nitro/types.h"

typedef struct {
    s16 x;
    s16 y;
} PanelPoint;

typedef struct {
    s32 x;
    s32 y;
} PanelPosition;

typedef struct {
    u8 pad_00[0x0c];
    int frontHandle;
    int backHandle;
    u8 pad_14[0x04];
} PanelSlot;

typedef struct {
    u8 pad_00[0x55];
    s8 layoutIndex;
    u8 pad_56;
    s8 slotCount;
    u8 pad_58[0x02];
    s8 swapThreshold;
    u8 pad_5b;
    s8 selectedSlot;
    u8 pad_5d[0x84 - 0x5d];
    PanelSlot slots[(0x65dc - 0x84) / 0x18];
    u8 pad_65dc[0x65dc - 0x84 - ((0x65dc - 0x84) / 0x18) * 0x18];
    void *records;
} PanelState;

extern PanelState *data_ov015_020812e0;
extern PanelPoint *gWirelessModeDataTables[];
extern unsigned int func_0202a9e4(unsigned int range);
extern void IndexedRecord_SetPair(void *recordBase, int recordIndex, PanelPosition *sourceValue);

BOOL SwapPanelSlots(int slotIndex) {
    PanelPosition position;
    PanelSlot saved;
    PanelPoint *points;
    int selected;
    int half;
    BOOL result = FALSE;

    if (data_ov015_020812e0->selectedSlot < 0) {
        return result;
    }
    if (data_ov015_020812e0->selectedSlot == slotIndex) {
        return TRUE;
    }
    half = data_ov015_020812e0->slotCount / 2;
    if (half <= 0) {
        return result;
    }
    half = func_0202a9e4((u16)half);
    if (half <= data_ov015_020812e0->swapThreshold) {
        points = gWirelessModeDataTables[data_ov015_020812e0->layoutIndex];
        saved = data_ov015_020812e0->slots[slotIndex];
        selected = data_ov015_020812e0->selectedSlot;
        data_ov015_020812e0->slots[slotIndex] = data_ov015_020812e0->slots[selected];
        data_ov015_020812e0->slots[selected] = saved;
        position.x = points[slotIndex].x << 12;
        position.y = points[slotIndex].y << 12;
        IndexedRecord_SetPair(data_ov015_020812e0->records, data_ov015_020812e0->slots[slotIndex].frontHandle, &position);
        IndexedRecord_SetPair(data_ov015_020812e0->records, data_ov015_020812e0->slots[slotIndex].backHandle, &position);
        position.x = points[selected].x << 12;
        position.y = points[selected].y << 12;
        IndexedRecord_SetPair(data_ov015_020812e0->records, data_ov015_020812e0->slots[selected].frontHandle, &position);
        IndexedRecord_SetPair(data_ov015_020812e0->records, data_ov015_020812e0->slots[selected].backHandle, &position);
        result = TRUE;
    }
    return result;
}
