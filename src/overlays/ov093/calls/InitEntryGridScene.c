#include "nitro/types.h"

typedef struct {
    u32 vramBase;
    u32 unk_04;
    u32 paletteBase;
    u8 resources[0x200 - 0xc];
    u8 animSets[2][0x6434];
    u8 pad_ca68[0xcf00 - 0xca68];
    int unk_CF00;
    u8 pad_cf04[0xcf4c - 0xcf04];
    int selectedIndex;
    int isClosing;
    u8 pad_cf54[0xd19c - 0xcf54];
    int unk_D19C;
    u8 pad_d1a0[0xd1b8 - 0xd1a0];
    int unk_D1B8;
    int unk_D1BC;
    int unk_D1C0;
    int isLocked;
    int popupHandle;
    int unk_D1CC;
    int unk_D1D0;
    int unk_D1D4;
    int unk_D1D8;
    int unk_D1DC;
    int unk_D1E0;
    u8 pad_d1e4[0xd224 - 0xd1e4];
} SceneWork;

typedef struct {
    u32 vramBase;
    void *resources;
    void *animSet;
    int unk_0C;
} PopupInit;

typedef struct {
    u8 pad_00[8];
    int value;
    u8 pad_0c[0x20];
} PanelDesc;

extern SceneWork *data_ov093_020c5100;
extern PanelDesc data_ov093_020c4058;
extern PanelDesc data_ov093_020c4084;
extern char sOv093_VblankFunc_020c4d54[];

extern void SetStateFlagBits(u8 clearMask, u8 setBits);
extern void MIi_CpuClearFast(u32 data, void *dst, u32 size);
extern void MIi_CpuCopyFast(const void *src, void *dst, u32 size);
extern BOOL IsGlobalPackedBitSet(int bitIndex);
extern void SetEntryFlag_020c22f4(int flagSet, int entryIndex);
extern BOOL IsEntryFlagSet_020c22c4(int flagSet, int entryIndex);
extern void func_ov093_020c0fd0(SceneWork *work);
extern BOOL AcquireRecordManager(void);
extern int AcquireRecordSlot(int slot, int param);
extern void func_ov093_020bf69c(SceneWork *work);
extern void func_ov093_020bf8a0(SceneWork *work);
extern void func_ov093_020bf904(SceneWork *work);
extern void func_ov093_020bfae4(SceneWork *work);
extern void InitEntrySlotSprites(SceneWork *work);
extern void RefreshEntryListSlots(SceneWork *work);
extern void UpdateDragAreaBounds(SceneWork *work);
extern void func_ov093_020c070c(PanelDesc *desc, SceneWork *work);
extern void RedrawEntryPanelText(int mode, SceneWork *work);
extern int func_ov093_020c3bfc(PopupInit *init);
extern void func_ov093_020c2b24(void);
extern void InvokeForChannelOrBoth(u32 arg0, u32 arg1, int arg2, int channel);
extern void SetSceneState(int state, SceneWork *work);

BOOL InitEntryGridScene(SceneWork *work)
{
    PanelDesc desc;
    PopupInit init;
    int i;
    int selected;

    data_ov093_020c5100 = work;
    SetStateFlagBits(5, 0);
    MIi_CpuClearFast(0, work, sizeof(SceneWork));
    work->isClosing = 0;
    work->unk_D19C = 0;
    work->unk_D1B8 = 0;
    work->unk_D1E0 = 0;
    work->unk_D1BC = 0;
    work->unk_D1C0 = 0;
    work->unk_D1CC = 0;
    work->unk_D1D4 = 0;
    work->unk_D1D8 = 0;
    work->unk_D1DC = 0;
    for (i = 0; i < 30; i++) {
        if (IsGlobalPackedBitSet(i + 0xf1a)) {
            SetEntryFlag_020c22f4(0, i);
        }
    }
    for (i = 0; i < 8; i++) {
        if (IsGlobalPackedBitSet(i + 0xf3c)) {
            SetEntryFlag_020c22f4(2, i);
        }
    }
    func_ov093_020c0fd0(work);
    selected = work->selectedIndex;
    if (IsEntryFlagSet_020c22c4(4, selected)) {
        SetEntryFlag_020c22f4(5, selected);
    }
    AcquireRecordManager();
    AcquireRecordSlot(0, 1);
    AcquireRecordSlot(9, 1);
    func_ov093_020bf69c(work);
    func_ov093_020bf8a0(work);
    func_ov093_020bf904(work);
    func_ov093_020bfae4(work);
    InitEntrySlotSprites(work);
    RefreshEntryListSlots(work);
    UpdateDragAreaBounds(work);
    func_ov093_020c070c(&data_ov093_020c4058, work);
    MIi_CpuCopyFast(&data_ov093_020c4084, &desc, sizeof(PanelDesc));
    desc.value = work->unk_D19C;
    func_ov093_020c070c(&desc, work);
    RedrawEntryPanelText(-1, work);
    init.vramBase = work->vramBase;
    init.resources = work->resources;
    init.animSet = work->animSets[1];
    init.unk_0C = work->unk_CF00;
    work->popupHandle = func_ov093_020c3bfc(&init);
    InvokeForChannelOrBoth(1, (u32)sOv093_VblankFunc_020c4d54, (int)func_ov093_020c2b24, 0);
    SetSceneState(1, work);
    return TRUE;
}



