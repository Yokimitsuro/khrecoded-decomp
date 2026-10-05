#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x2c];
    int pageIndex;
    int pageOffset;
} PageState;

typedef struct {
    u8 pad_0000[0xcf4c];
    int selectedIndex;
    int isClosing;
    PageState pager;
    u8 pad_cf88[0xd1c4 - 0xcf88];
    int isLocked;
    u8 pad_d1c8[0xd21c - 0xd1c8];
    int unk_D21C;
} SceneWork;

extern SceneWork *data_ov093_020c5100;

extern int func_ov093_020c2368(void);
extern BOOL IsEntryFlagSet_020c22c4(int flagSet, int entryIndex);
extern void SetEntryFlag_020c22f4(int flagSet, int entryIndex);
extern void SetGlobalPackedBit(int bitIndex);
extern void SetSlotAnimFlag(int side, int slotIndex, int value, SceneWork *work);
extern void RestartSlotAnim(int side, int slotIndex, BOOL enabled, SceneWork *work);
extern void RedrawEntryPanelText(int mode, SceneWork *work);
extern BOOL PlaySoundEffect(int seqArcNo, int index);
extern BOOL ScrollBarStepDown(int mode, SceneWork *work);
extern void ResetSmoothValue(int index);
extern void RefreshEntryListSlots(SceneWork *work);

void FinishGridPageScrollDual(SceneWork *work)
{
    PageState *pager;
    int entryIndex;
    int i;
    int unlocked;
    BOOL seen;
    u32 scroll;

    if (func_ov093_020c2368() != 6) {
        return;
    }
    if (work->isClosing == 0 && work->isLocked == 0) {
        if (!ScrollBarStepDown(0, work)) {
            return;
        }
        ResetSmoothValue(0);
        data_ov093_020c5100->unk_D21C = 0;
        pager = &work->pager;
        entryIndex = work->selectedIndex % 5 + (pager->pageIndex + pager->pageOffset) * 5;
        work->selectedIndex = entryIndex;
        if (IsEntryFlagSet_020c22c4(4, entryIndex)) {
            SetEntryFlag_020c22f4(5, entryIndex);
            SetGlobalPackedBit(entryIndex + 0x1202);
        }
        for (i = 0; i < 10; i++) {
            entryIndex = pager->pageIndex * 5;
            unlocked = IsEntryFlagSet_020c22c4(4, i + entryIndex);
            seen = IsEntryFlagSet_020c22c4(5, i + entryIndex) != 0;
            SetSlotAnimFlag(0, i + 3, unlocked, work);
            RestartSlotAnim(0, i + 3, seen, work);
        }
        PlaySoundEffect(0, 0);
        RedrawEntryPanelText(0, work);
        scroll = ((u32)(work->pager.pageIndex * 48) << 16) & 0x01ff0000;
        *(vu32 *)0x0400001c = scroll;
        *(vu32 *)0x04000010 = scroll;
    } else {
        if (!ScrollBarStepDown(1, work)) {
            return;
        }
        ResetSmoothValue(0);
        data_ov093_020c5100->unk_D21C = 0;
        if (work->isLocked == 0) {
            PlaySoundEffect(0, 0);
        }
        RedrawEntryPanelText(1, work);
        RefreshEntryListSlots(work);
    }
}



