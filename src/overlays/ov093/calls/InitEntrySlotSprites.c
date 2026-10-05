#include "nitro/types.h"

typedef struct {
    int animIndex;
    u8 pad_04[0x18];
} SlotEntry;

typedef struct {
    u8 data[0x1c];
} SlotTemplate;

typedef struct {
    u32 vramAttr;
    int mode;
    int unk_08;
    int unk_0C;
} ObjManagerParams;

typedef struct {
    u32 vramBase;
    u32 unk_04;
    u32 paletteBase;
    u8 pad_000c[0x200 - 0xc];
    u8 animSets[2][0x6434];
    SlotEntry leftSlots[13];
    SlotEntry rightSlots[30];
} SceneWork;

extern SlotTemplate data_ov093_020c4128[13];
extern SlotTemplate data_ov093_020c4294[30];

extern void InitObjManager(void *manager, ObjManagerParams *params);
extern void PXI_Init_0204f020(void *manager, u32 attr);
extern void CreateSlotAnim(int side, int slotIndex, SlotTemplate *tmpl, SceneWork *work);
extern BOOL IsEntryFlagSet_020c22c4(int flagSet, int entryIndex);
extern void SetSlotAnimFlag(int side, int slotIndex, int value, SceneWork *work);
extern void RestartSlotAnim(int side, int slotIndex, BOOL enabled, SceneWork *work);
extern void SetGlobalPackedBit(int bitIndex);
extern void IndexedRecord_ClearActive(void *manager, int animIndex);

void InitEntrySlotSprites(SceneWork *work)
{
    ObjManagerParams params;
    int entry;
    int i;
    int unlocked;
    void *rightSet;
    BOOL seen;

    i = 0;
    params.vramAttr = ((work->vramBase + 0x8000) & 0xfffffc) << 7 | 0x80000006;
    params.mode = 1;
    params.unk_08 = 0;
    params.unk_0C = 0;
    InitObjManager(work->animSets[0], &params);
    PXI_Init_0204f020(work->animSets[0], ((work->paletteBase + 0x8000) & 0xfffffc) << 7 | 0x80000000);
    for (; i < 13; i++) {
        CreateSlotAnim(0, i, &data_ov093_020c4128[i], work);
    }
    for (entry = 0; entry < 10; entry++) {
        unlocked = IsEntryFlagSet_020c22c4(4, entry);
        seen = IsEntryFlagSet_020c22c4(5, entry) != 0;
        SetSlotAnimFlag(0, entry + 3, unlocked, work);
        RestartSlotAnim(0, entry + 3, seen, work);
        if (entry == 0 && unlocked) {
            SetGlobalPackedBit(0x1202);
        }
    }
    params.vramAttr = ((work->vramBase + 0x8000) & 0xfffffc) << 7 | 0x80000002;
    params.mode = 2;
    params.unk_08 = 0;
    params.unk_0C = 0;
    rightSet = work->animSets[1];
    InitObjManager(rightSet, &params);
    for (i = 0; i < 30; i++) {
        CreateSlotAnim(1, i, &data_ov093_020c4294[i], work);
    }
    for (i = 20; i < 30; i++) {
        IndexedRecord_ClearActive(rightSet, work->rightSlots[i].animIndex);
    }
}









