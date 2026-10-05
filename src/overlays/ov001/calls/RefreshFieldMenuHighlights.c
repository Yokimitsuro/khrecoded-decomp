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
    s32 hidden;
    u8 pad_124[0x4];
    s32 unk_128;
    u8 pad_12C[0x8];
    s32 unk_134;
} FieldMenu;

extern int func_ov001_0207123c(void);
extern u16 *func_ov027_020b9e10(int layers, int layerIndex);
extern void *GetSceneTagTracker(void);
extern FieldEntry *CycleMenuEntry(FieldMenu *menu, s32 index, s32 slot, s32 *outValue);
extern void func_ov001_02075b48(FieldMenu *menu, FieldEntry *entry, u16 *screen, s32 slot, s32 kind, s32 row, s32 palette);
extern void func_ov027_020b824c(void *tracker, void *record, s16 x, s16 y);
extern void func_ov027_020b9d74(int layers, int layerIndex, int x, int y, int width, int height);
extern BOOL IsModeSetOrFlag370aClear(void);
extern BOOL IsFieldFlag10Set(void);
extern BOOL IsHudFlag7Set(void);
extern void func_ov001_02075db8(FieldMenu *menu);
extern void UpdateFieldPromptTag(FieldMenu *menu, void *tracker);
extern BOOL func_ov001_020728a4(void);
extern void *FindActiveRecordById(void *pool, u16 recordId);
extern void func_ov027_020b8230(void *pool, void *record);
extern void InvokeCallback40_020b8268(void *pool, void *record);
extern void FillBackgroundLayerRect_02001a60(void *info, u16 *dst, int x, int y, u8 palette);

void RefreshFieldMenuHighlights(FieldMenu *menu)
{
    int layers = func_ov001_0207123c();
    u16 *screen = func_ov027_020b9e10(layers, 0xb);
    void *tracker = GetSceneTagTracker();
    s32 i;
    s32 row;
    FieldEntry *entry;
    s32 slotIndex;
    void *record;

    if (menu->hidden != 0) {
        return;
    }
    if (!IsModeSetOrFlag370aClear() || IsFieldFlag10Set() || IsHudFlag7Set()) {
        row = 0x14;
        if (IsModeSetOrFlag370aClear() && menu->unk_C8 > 0) {
            entry = CycleMenuEntry(menu, menu->entryIndex, 1, NULL);
            if (entry->flags & 2) {
                func_ov027_020b9d74(layers, 0xb, 0, row, 0xb, 2);
                func_ov001_02075b48(menu, entry, screen, 2, 2, row, 1);
                UpdateFieldPromptTag(menu, tracker);
            }
            row -= 2;
        }
        if (menu->unk_68 != 10) {
            record = FindActiveRecordById(tracker, 0x21);
        } else {
            record = FindActiveRecordById(tracker, 0x24);
        }
        func_ov027_020b8230(tracker, record);
        func_ov027_020b824c(tracker, FindActiveRecordById(tracker, 0xe), 0, row);
        return;
    }
    for (i = -(menu->unk_C8 >= 3); i < 2; i++) {
        entry = CycleMenuEntry(menu, menu->entryIndex, i + 1, &slotIndex);
        if (entry->flags & 2) {
            row = i * 2 + 0x12;
            func_ov027_020b9d74(layers, 0xb, 0, row, 0xb, 2);
            if (i == 0 && (entry->flags & 1) && (entry->flags & 4) && menu->unk_68 != 10) {
                func_ov001_02075b48(menu, entry, screen, i + 1, 2, row, 1);
                UpdateFieldPromptTag(menu, tracker);
            } else {
                func_ov001_02075b48(menu, entry, screen, i + 1, 1, row, 9);
                func_ov027_020b824c(tracker, menu->cursorRecord, 0, row);
            }
        }
    }
}
