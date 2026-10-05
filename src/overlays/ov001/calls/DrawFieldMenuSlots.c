#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x28];
    u16 flags;
    u8 pad_2A[2];
    s32 unk_2C;
} FieldEntry;

typedef struct {
    u8 pad_000[0x34];
    u8 layer[0x34];
    s32 unk_68;
    u8 pad_06C[0x5C];
    s32 unk_C8;
    u8 pad_0CC[0x20];
    s32 entryIndex;
    s32 groupIndex;
    u8 pad_0F4[0x8];
    s32 state;
    u8 pad_100[0x4];
    s32 mode;
    s32 idleCount;
    u8 pad_10C[0x10];
    void *cursorRecord;
    u8 pad_120[0x8];
    s32 unk_128;
    u8 pad_12C[0x8];
    s32 unk_134;
} FieldMenu;

extern int func_ov001_0207123c(void);
extern u16 *func_ov027_020b9e10(int layers, int layerIndex);
extern void *GetSceneTagTracker(void);
extern FieldEntry *CycleMenuEntry(FieldMenu *menu, s32 index, s32 slot, s32 *outValue);
extern void func_ov001_02075b48(FieldMenu *menu, FieldEntry *entry, u16 *screen, s32 slot, s32 kind, s32 row, s32 palette);
extern void func_ov027_020b824c(void *tracker, void *record, u16 x, u16 y);
extern void func_ov001_02075db8(FieldMenu *menu);
extern void func_ov001_02075ccc(FieldMenu *menu, void *tracker);
extern BOOL IsFieldFlag8Set(void);
extern void *FindActiveRecordById(void *pool, u16 recordId);
extern void func_ov027_020b8230(void *pool, void *record);
extern void func_ov027_020b8288(void *pool, void *record);
extern void FillBackgroundLayerRect(void *info, u16 *dst, int x, int y, u8 palette);

void DrawFieldMenuSlots(FieldMenu *menu)
{
    u16 *screen = func_ov027_020b9e10(func_ov001_0207123c(), 0xb);
    void *tracker = GetSceneTagTracker();
    s32 first = -(menu->unk_C8 >= 3);
    s32 i;
    FieldEntry *entry;
    s32 slotIndex;
    void *record;

    for (i = first; i < 2; i++) {
        entry = CycleMenuEntry(menu, menu->groupIndex, i + 1, &slotIndex);
        func_ov001_02075b48(menu, entry, screen, i + 1, 1, i * 2 + 0x11, 9);
    }
    if (first == 0) {
        switch (menu->mode) {
        case 0:
            entry = CycleMenuEntry(menu, 2, 1, NULL);
            break;
        case 1:
            entry = CycleMenuEntry(menu, 0xe, 1, NULL);
            break;
        case 2:
            entry = CycleMenuEntry(menu, 2, 1, NULL);
            break;
        }
        func_ov001_02075b48(menu, entry, screen, 0, 1, 0x10, 9);
    }
    if (menu->unk_68 != 10) {
        record = FindActiveRecordById(tracker, 0x21);
    } else {
        record = FindActiveRecordById(tracker, 0x24);
    }
    func_ov027_020b8230(tracker, record);
    func_ov027_020b824c(tracker, menu->cursorRecord, 0, 0x11);
    func_ov027_020b824c(tracker, menu->cursorRecord, 0, 0x13);
    if (first == 0) {
        func_ov027_020b824c(tracker, menu->cursorRecord, 0, 0x10);
    } else {
        func_ov027_020b824c(tracker, menu->cursorRecord, 0, 0xf);
    }
    if (menu->unk_68 != 10) {
        if (IsFieldFlag8Set()) {
            func_ov027_020b8230(tracker, FindActiveRecordById(tracker, menu->mode == 1 ? 0xd : 0xe));
        } else {
            func_ov027_020b8230(tracker, FindActiveRecordById(tracker, 0xc));
        }
    } else {
        func_ov027_020b8288(tracker, FindActiveRecordById(tracker, 0xc));
    }
    FillBackgroundLayerRect(menu->layer, screen, 2, 0x16, menu->unk_128 != 0 ? 9 : 10);
    menu->state = 5;
    menu->idleCount = 0;
}
