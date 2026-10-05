#include "nitro/types.h"

typedef struct {
    int id;
    u8 pad_04[0x28];
    int scrollPos;
    u8 pad_30[0x1c];
} ScrollBar;

typedef struct {
    int *record;
    u8 pad_04[8];
} ListEntry;

typedef struct {
    u8 pad_0000[0xcf54];
    ScrollBar bars[2];
    u8 pad_cfec[4];
    ListEntry entries[1];
} SceneWork;

extern void SetSlotAnimFlag(int side, int slotIndex, int value, SceneWork *work);
extern BOOL IsEntryFlagSet_020c22c4(int flagSet, int entryIndex);
extern void RestartSlotAnim(int side, int slotIndex, int frame, SceneWork *work);

void RefreshEntryListSlots(SceneWork *work)
{
    ScrollBar *bar = &work->bars[1];
    int i;
    int entryId;

    for (i = 0; i < 9; i++) {
        entryId = *work->entries[i + bar->scrollPos].record;
        if (entryId == -1) {
            SetSlotAnimFlag(1, i + 0x14, 0, work);
        } else {
            SetSlotAnimFlag(1, i + 0x14, 1, work);
            if (IsEntryFlagSet_020c22c4(0, entryId) || IsEntryFlagSet_020c22c4(1, entryId)) {
                RestartSlotAnim(1, i + 0x14, 1, work);
            } else {
                RestartSlotAnim(1, i + 0x14, 0, work);
            }
        }
    }
}
