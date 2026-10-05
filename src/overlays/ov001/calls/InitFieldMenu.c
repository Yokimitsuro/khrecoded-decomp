#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x6C];
    s32 unk_6C;
    u8 pad_070[0xA8];
    s32 unk_118;
    void *record;
    u8 pad_120[0x18];
    s32 unk_138;
    u8 pad_13C[0x8];
    s32 unk_144;
    u8 pad_148[0x4];
    s32 unk_14C;
} FieldMenu;

typedef struct {
    u32 unk_00;
    FieldMenu *menu;
} FieldMenuHandle;

extern FieldMenuHandle data_ov001_020a04d0;

extern FieldMenu *NNSi_FndGetCurrentRootHeap(void);
extern void *GetSceneTagTracker(void);
extern void MI_CpuFill8(void *dst, int value, u32 size);
extern s8 func_ov001_02068084(void);
extern BOOL func_ov001_020645c8(u32 flagId);
extern void *FindActiveRecordById(void *pool, u32 recordId);
extern void func_ov001_0207723c(FieldMenu *menu, u32 arg);
extern void func_ov001_020769f4(FieldMenu *menu);
extern int UpdateFieldMenu(void);

void *InitFieldMenu(u32 *params)
{
    FieldMenu *menu = NNSi_FndGetCurrentRootHeap();
    void *tracker = GetSceneTagTracker();

    data_ov001_020a04d0.menu = menu;
    MI_CpuFill8(menu, 0, sizeof(FieldMenu));
    menu->unk_14C = 1;
    menu->unk_118 = 1;
    menu->unk_6C = -1;
    menu->unk_138 = !(func_ov001_02068084() == 0 && func_ov001_020645c8(0x3520));
    menu->unk_144 = -1;
    menu->record = FindActiveRecordById(tracker, 0x20);
    func_ov001_0207723c(menu, *params);
    func_ov001_020769f4(menu);
    return UpdateFieldMenu;
}
