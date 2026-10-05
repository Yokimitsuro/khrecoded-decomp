#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x28];
    u16 flags;
    u16 count;
} GaugeEntry;

typedef struct {
    u8 pad_000[0x34];
    u8 layer[0x34];
    s32 unk_68;
    u8 pad_06C[0x5C];
    s32 unk_C8;
    u8 pad_0CC[0x20];
    s32 unk_EC;
    u8 pad_0F0[0x14];
    s32 unk_104;
    u8 pad_108[0x14];
    s32 unk_11C;
    u8 pad_120[8];
    s32 unk_128;
} FieldMenu;

extern int func_ov001_0207123c(void);
extern u16 *func_ov027_020b9e10(int layers, int layerIndex);
extern void *GetSceneTagTracker(void);
extern GaugeEntry *CycleMenuEntry(FieldMenu *menu, s32 group, s32 slot, s32 *outIndex);
extern void func_ov001_02075b48(FieldMenu *menu, GaugeEntry *entry, u16 *screen, s32 slot, s32 mode, s32 row,
                                s32 palette);
extern void UpdateFieldPromptTag(FieldMenu *menu, void *tracker);
extern void func_ov027_020b824c(void *tracker, s32 handle, u16 arg2, u16 arg3);
extern void *FindActiveRecordById(void *tracker, u16 recordId);
extern void func_ov027_020b8230(void *tracker, void *record);
extern void func_ov027_020b8288(void *tracker, void *record);
extern BOOL IsFieldFlag8Set(void);
extern void FillBackgroundLayerRect(void *info, u16 *dst, int x, int y, u8 palette);

void DrawPartyGaugeFrames(FieldMenu *menu)
{
    u16 *screen;
    void *tracker;
    GaugeEntry *entry;
    s32 index;
    s32 mode;
    s32 slot;

    screen = func_ov027_020b9e10(func_ov001_0207123c(), 11);
    tracker = GetSceneTagTracker();
    for (index = -1; index < 2; index++) {
        if ((menu->unk_C8 == 2 && index == -1) || (menu->unk_C8 == 1 && index != 0)) {
            switch (menu->unk_104) {
            case 0:
                slot = 2;
                entry = CycleMenuEntry(menu, slot, 1, NULL);
                break;
            case 1:
                entry = CycleMenuEntry(menu, 14, 1, NULL);
                break;
            case 2:
                entry = CycleMenuEntry(menu, 2, 1, NULL);
                break;
            }
        } else {
            entry = CycleMenuEntry(menu, menu->unk_EC, index + 1, &slot);
        }
        mode = (index == 0 && (entry->flags & 1) && (entry->flags & 4) && menu->unk_68 != 10) ? 2 : 1;
        func_ov001_02075b48(menu, entry, screen, index + 1, mode, index * 2 + 18, mode == 2 ? 1 : 9);
    }
    entry = CycleMenuEntry(menu, menu->unk_EC, 1, NULL);
    if ((entry->flags & 1) && (entry->flags & 4) && menu->unk_68 != 10) {
        UpdateFieldPromptTag(menu, tracker);
    } else {
        func_ov027_020b824c(tracker, menu->unk_11C, 0, 0x12);
    }
    if (menu->unk_68 != 10) {
        func_ov027_020b8230(tracker, FindActiveRecordById(tracker, 0x21));
    } else {
        func_ov027_020b8230(tracker, FindActiveRecordById(tracker, 0x24));
    }
    func_ov027_020b824c(tracker, menu->unk_11C, 0, 0x10);
    func_ov027_020b824c(tracker, menu->unk_11C, 0, 0x14);
    if (menu->unk_68 != 10) {
        if (IsFieldFlag8Set()) {
            func_ov027_020b8230(tracker,
                                               FindActiveRecordById(tracker, menu->unk_104 == 1 ? 0xD : 0xE));
        } else {
            func_ov027_020b8230(tracker, FindActiveRecordById(tracker, 0xC));
        }
    } else {
        func_ov027_020b8288(tracker, FindActiveRecordById(tracker, 0xC));
    }
    FillBackgroundLayerRect(menu->layer, screen, 2, 22, menu->unk_128 != 0 ? 9 : 10);
}
