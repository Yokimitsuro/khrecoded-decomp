#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x28];
    u16 flags;
} FieldEntry;

typedef struct {
    u8 pad_000[0x34];
    u8 layer[0x34];
    s32 unk_68;
    u8 pad_06C[0x5C];
    s32 unk_C8;
    u8 pad_0CC[0x20];
    s32 entryIndex;
    u8 pad_0F0[0xC];
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
extern void UpdateFieldPromptTag(FieldMenu *menu, void *tracker);
extern BOOL IsFieldFlag8Set(void);
extern u64 _s32_div_f(s32 dividend, s32 divisor);
extern void *FindActiveRecordById(void *pool, u16 recordId);
extern void func_ov027_020b8230(void *pool, void *record);
extern void func_ov027_020b8288(void *pool, void *record);
extern void FillBackgroundLayerRect(void *info, u16 *dst, int x, int y, u8 palette);

static inline BOOL IsEntryActive(FieldEntry *entry)
{
    BOOL active = FALSE;
    if ((entry->flags & 1) && (entry->flags & 4)) {
        active = TRUE;
    }
    return active;
}

static inline BOOL IsEntrySelectable(FieldMenu *menu, FieldEntry *entry)
{
    BOOL selectable = FALSE;
    if (IsEntryActive(entry) && menu->unk_68 != 10) {
        selectable = TRUE;
    }
    return selectable;
}

void RefreshFieldMenuSlotsWrapped(FieldMenu *menu, s32 level)
{
    u16 *screen = func_ov027_020b9e10(func_ov001_0207123c(), 0xb);
    void *tracker = GetSceneTagTracker();
    BOOL ready = FALSE;
    s32 i = -1;
    s32 limit = level * 3 - 7;
    FieldEntry *entry;
    s32 kind;
    s32 slotIndex;

    do {
        if (menu->unk_C8 < 3 && i == -1) {
            switch (menu->mode) {
            case 0:
                slotIndex = 2;
                entry = CycleMenuEntry(menu, 2, 1, NULL);
                break;
            case 1:
                entry = CycleMenuEntry(menu, 0xe, 1, NULL);
                break;
            case 2:
                entry = CycleMenuEntry(menu, 2, 1, NULL);
                break;
            }
        } else {
            slotIndex = (s32)(_s32_div_f(menu->entryIndex + i + menu->unk_C8, menu->unk_C8) >> 32);
            entry = CycleMenuEntry(menu, menu->entryIndex, i + 1, &slotIndex);
        }
        switch (i) {
        case -1:
            kind = 1;
            break;
        case 0:
            kind = IsEntrySelectable(menu, entry) ? 2 : 1;
            break;
        case 1:
            kind = limit;
            if (kind >= 1) {
                kind = 1;
                ready = TRUE;
            }
            break;
        }
        func_ov001_02075b48(menu, entry, screen, i + 1, kind, i * 2 + 0x12, kind == 2 ? 1 : 9);
        i++;
    } while (i < 2);

    entry = CycleMenuEntry(menu, menu->entryIndex, 1, NULL);
    if ((entry->flags & 1) && (entry->flags & 4) && menu->unk_68 != 10) {
        UpdateFieldPromptTag(menu, tracker);
    } else {
        func_ov027_020b824c(tracker, menu->cursorRecord, 0, 0x12);
    }
    if (menu->unk_68 != 10) {
        func_ov027_020b8230(tracker, FindActiveRecordById(tracker, 0x21));
    } else {
        func_ov027_020b8230(tracker, FindActiveRecordById(tracker, 0x24));
    }
    func_ov027_020b824c(tracker, menu->cursorRecord, 0, 0x10);
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
    if (ready) {
        menu->state = 0;
        menu->idleCount = 0;
        menu->unk_134 = 0;
        func_ov027_020b824c(tracker, menu->cursorRecord, 0, 0x14);
    } else {
        menu->idleCount++;
    }
}
