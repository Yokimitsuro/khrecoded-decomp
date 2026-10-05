#include "nitro/types.h"

typedef struct ListEntry {
    u16 count;
    u16 pad_02;
    u16 recordIndex;
} ListEntry;

typedef struct ItemList {
    u8 pad_0000[0xc];
    u8 keepEntry;
    u8 pad_000D[0x3c18 - 0xd];
    ListEntry *entries[(0x4d86 - 0x3c18) / 4];
    u8 pad_4D84[2];
    s16 cursorIndex;
    u8 pad_4D88[0x7f9c - 0x4d88];
    s32 state;
} ItemList;

extern void ReleaseRecordEntry(int index);
extern BOOL func_ov076_020ca918(ItemList *list);

void ItemList_ReleaseCursorEntry(ItemList *list)
{
    if (list->keepEntry == 0) {
        ListEntry *entry = list->entries[list->cursorIndex];
        entry->count = 0;
        ReleaseRecordEntry(entry->recordIndex);
    }
    list->state = 4;
    func_ov076_020ca918(list);
}
