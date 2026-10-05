#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x34];
    u8 layer[0xc8 - 0x34];
    s32 entryCount;
    u8 pad_0cc[0xec - 0xcc];
    s32 selectedIndex;
    u8 pad_0f0[0x128 - 0xf0];
    s32 highlighted;
} FieldMenu;

extern void *GetSceneTagTracker(void);
extern int func_ov001_0207123c(void);
extern u16 *func_ov027_020b9e10(int layer, int index);
extern BOOL IsModeSetOrFlag370aClear(void);
extern void *CycleMenuEntry(FieldMenu *menu, s32 index, s32 slot, s32 flags);
extern void func_ov001_02075b48(FieldMenu *menu, void *entry, u16 *screen, s32 slot, s32 kind, s32 row, s32 palette);
extern void UpdateFieldPromptTag(FieldMenu *menu, void *pool);
extern void FillBackgroundLayerRect(void *info, u16 *dst, int x, int y, u8 palette);
extern void *FindActiveRecordById(void *pool, u32 recordId);
extern void func_ov027_020b8230(void *pool, void *record);
extern void func_ov027_020b824c(void *pool, void *record, int first, s16 second);

void DrawFieldMenuPanel(FieldMenu *menu) {
    void *pool = GetSceneTagTracker();
    u16 *screen = func_ov027_020b9e10(func_ov001_0207123c(), 0xb);
    int row = 0x14;
    int palette;

    if (IsModeSetOrFlag370aClear() && menu->entryCount > 0) {
        func_ov001_02075b48(menu, CycleMenuEntry(menu, menu->selectedIndex, 1, 0), screen, 2, 2, row, 1);
        UpdateFieldPromptTag(menu, pool);
        row -= 2;
    }
    if (menu->highlighted != 0) {
        palette = 9;
    } else {
        palette = 10;
    }
    FillBackgroundLayerRect(menu->layer, screen, 2, 0x16, palette);
    func_ov027_020b8230(pool, FindActiveRecordById(pool, 0x21));
    func_ov027_020b824c(pool, FindActiveRecordById(pool, 0xe), 0, row);
}
