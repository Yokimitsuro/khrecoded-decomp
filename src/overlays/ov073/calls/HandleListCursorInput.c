#include "nitro/types.h"

typedef struct ListEntry {
    u16 unk_0;
    u16 column;
    u32 unk_4;
} ListEntry;

typedef struct ListTable {
    u8 pad_00[8];
    ListEntry entries[1];
} ListTable;

typedef struct ListData {
    u8 pad_00[4];
    ListTable *table;
} ListData;

typedef struct ListView {
    u8 pad_00[4];
    ListData *data;
    u8 pad_08[0x94 - 0x08];
    int scrollX;
    int targetX;
    BOOL scrolling;
    u8 pad_a0[8];
    int selectedIndex;
} ListView;

typedef BOOL (*CompareFunc)(int a, int b);

extern int func_ov001_02064784(void);
extern BOOL func_ov001_020645c8(u32 value);
extern int FindVerticalNeighbor_020c3810(ListView *list, CompareFunc rejectFunc, CompareFunc closerFunc);
extern int func_ov073_020c388c(ListView *list, int direction);
extern BOOL IsGreaterOrEqual_020c37e0(int a, int b);
extern BOOL IsGreaterThan_020c37ec(int a, int b);
extern BOOL IsLessOrEqual_020c37f8(int a, int b);
extern BOOL IsLessThan_020c3804(int a, int b);
extern void SelectListEntry(ListView *list, int entryIndex);
extern BOOL TrySelectListEntry_020c37a8(ListView *list, int entryIndex);
extern BOOL PlaySoundEffect(int seqArcNo, int index);

void HandleListCursorInput(ListView *list, u32 input)
{
    ListTable *table = list->data->table;
    int next = -1;
    int position;
    int offset;

    if (func_ov001_02064784() == 0 && func_ov001_020645c8(0x370b)) {
        return;
    }
    if (input & 0x40) {
        next = FindVerticalNeighbor_020c3810(list, IsGreaterOrEqual_020c37e0, IsGreaterThan_020c37ec);
    } else if (input & 0x80) {
        next = FindVerticalNeighbor_020c3810(list, IsLessOrEqual_020c37f8, IsLessThan_020c3804);
    } else if (input & 0x20) {
        next = func_ov073_020c388c(list, -0x10);
    } else if (input & 0x10) {
        next = func_ov073_020c388c(list, 0x10);
    }
    if (next >= 0) {
        SelectListEntry(list, next);
        offset = (table->entries[list->selectedIndex].column - 2) * 8;
        position = offset + list->scrollX;
        if (position < 0) {
            list->targetX = -offset;
            list->scrolling = TRUE;
        }
        if (position > 0x80) {
            list->targetX = -(offset - 0x80);
            list->scrolling = TRUE;
        }
        PlaySoundEffect(0, 0);
    }
    if (input & 1) {
        if (!TrySelectListEntry_020c37a8(list, list->selectedIndex)) {
            PlaySoundEffect(0, 4);
            return;
        }
        PlaySoundEffect(0, 0x4d);
    }
}
