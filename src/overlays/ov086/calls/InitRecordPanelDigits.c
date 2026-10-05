#include "nitro/types.h"

typedef struct {
    u32 cellFileId;
    u32 unk04[3];
} ObjManagerConfig;

typedef struct {
    int x;
    int y;
} CellPosition;

typedef struct {
    int gaps[9];
} DigitGapTable;

typedef struct {
    u8 pad000[0x110];
    int digitCells[9];
} RecordPanel;

extern u8 *data_0205fe0c;
extern const ObjManagerConfig data_ov086_020c2148;
extern const DigitGapTable data_ov086_020c22ac;
extern void *func_ov039_020bc1ec(void);
extern u32 BuildSlotImageParams(int slot, u32 low);
extern int InitializeResourceContainer(void *container, void *config);
extern void InitObjManagerAndMark(void *container, ObjManagerConfig *config);
extern void func_ov027_020b9098(void *container, u32 value);
extern void func_ov027_020b8fb8(void *container, u32 fileId, int count);
extern void SetAllElementObjectModes(void *container, int mode);
extern void AddTaggedIndexedRecord(void *container, int layer, CellPosition *position, u32 digit);
extern int PXI_Init_0204f0c8(void *manager, u32 source, int enable);
extern void IndexedRecord_SetPair(void *manager, int cell, CellPosition *position);
extern void IndexedRecord_ClearActive(void *manager, int cell);
extern void func_0204f218(void *widget, int cell, u16 frame);
extern void IndexedRecords_SetFlag2(void *widget, int cell, BOOL visible);
extern void func_ov027_020b90a8(void *container, int elementId, void (*callback)(void));
extern void OnSliderTouched(void);

void InitRecordPanelDigits(RecordPanel *panel)
{
    void *container = func_ov039_020bc1ec();
    ObjManagerConfig config = data_ov086_020c2148;
    CellPosition position;
    DigitGapTable gapTable;
    int i;
    int x;
    u32 value;
    u32 digit;

    value = *(u32 *)(data_0205fe0c + 0x28d0);
    config.cellFileId = BuildSlotImageParams(2, 0x15);
    InitializeResourceContainer(container, NULL);
    InitObjManagerAndMark(container, &config);
    func_ov027_020b9098(container, BuildSlotImageParams(3, 0));
    func_ov027_020b8fb8(container, BuildSlotImageParams(2, 0x14), 0x11);
    SetAllElementObjectModes(container, 1);
    x = 0x43;
    position.y = 0xa4000;
    do {
        position.x = x << 12;
        digit = value % 10;
        value /= 10;
        AddTaggedIndexedRecord(container, 0, &position, digit);
        x -= 7;
    } while (value != 0);
    gapTable = data_ov086_020c22ac;
    position.y = 0xb4000;
    x = 0x43;
    for (i = 0; i < 9; i++) {
        panel->digitCells[i] = PXI_Init_0204f0c8(container, 1, 0);
        position.x = x << 12;
        IndexedRecord_SetPair(container, panel->digitCells[i], &position);
        IndexedRecord_ClearActive(container, panel->digitCells[i]);
        x -= gapTable.gaps[i];
    }
    func_0204f218(container, panel->digitCells[2], 10);
    func_0204f218(container, panel->digitCells[5], 10);
    IndexedRecords_SetFlag2(container, panel->digitCells[7], FALSE);
    IndexedRecords_SetFlag2(container, panel->digitCells[8], FALSE);
    func_ov027_020b90a8(container, 0x15, OnSliderTouched);
}
