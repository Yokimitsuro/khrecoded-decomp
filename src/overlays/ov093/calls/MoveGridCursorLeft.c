#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x2c];
    int pageIndex;
    int pageOffset;
} PageState;

typedef struct {
    u8 pad_0000[0xcaa8];
    int unk_CAA8;
    u8 pad_caac[0xcf4c - 0xcaac];
    int selectedIndex;
    int isClosing;
    PageState pager;
    u8 pad_cf88[0xd1c4 - 0xcf88];
    int isLocked;
    u8 pad_d1c8[0xd21c - 0xd1c8];
    int unk_D21C;
} SceneWork;

extern SceneWork *data_ov093_020c5100;
extern u16 data_02060500;

extern int func_ov093_020c2368(void);
extern BOOL IsEntryFlagSet_020c22c4(int flagSet, int entryIndex);
extern void SetEntryFlag_020c22f4(int flagSet, int entryIndex);
extern void SetGlobalPackedBit(int bitIndex);
extern void RestartSlotAnim(int side, int slotIndex, BOOL enabled, SceneWork *work);
extern void SetSlotPosition(int side, int layer, int offset, int value, SceneWork *work);
extern void RedrawEntryPanelText(int mode, SceneWork *work);
extern BOOL PlaySoundEffect(int seqArcNo, int index);
extern BOOL ConsumeScrollBarStep(int mode, SceneWork *work);
extern void ResetSmoothValue(int index);
extern void RefreshEntryListSlots(SceneWork *work);

void MoveGridCursorLeft(SceneWork *work)
{
    PageState *pager;
    int entryIndex;
    int column;
    int page;

    if (func_ov093_020c2368() != 6) {
        return;
    }
    if (work->isClosing == 0 && work->isLocked == 0) {
        pager = &work->pager;
        column = work->selectedIndex % 5 - 1;
        page = pager->pageIndex + pager->pageOffset;
        if (column < 0 && (data_02060500 & 0x20) != 0) {
            column = 4;
        }
        if (column < 0) {
            return;
        }
        entryIndex = column + page * 5;
        work->selectedIndex = entryIndex;
        if (IsEntryFlagSet_020c22c4(4, entryIndex)) {
            SetEntryFlag_020c22f4(5, entryIndex);
            SetGlobalPackedBit(entryIndex + 0x1202);
        }
        for (entryIndex = 0; entryIndex < 10; entryIndex++) {
            RestartSlotAnim(0, entryIndex + 3, IsEntryFlagSet_020c22c4(5, entryIndex + pager->pageIndex * 5) != 0, work);
        }
        SetSlotPosition(0, 2, (column + 1) * 0x2c, work->unk_CAA8, work);
        RedrawEntryPanelText(0, work);
        PlaySoundEffect(0, 0);
    } else {
        if (!ConsumeScrollBarStep(1, work)) {
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




