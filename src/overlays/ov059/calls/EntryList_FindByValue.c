#include "nitro/types.h"

typedef struct {
    u32 value;
    s32 kind;
} ListEntry;

typedef struct {
    u8 pad_000[0x60];
    ListEntry entries[24];
    u8 count;
} EntryList;

u32 EntryList_FindByValue(EntryList *list, u32 value)
{
    u32 index = 0;

    if (index < list->count) {
        do {
            ListEntry *entry = &list->entries[index];
            if (entry->value == value) {
                return index;
            }
            index = (index + 1) & 0xff;
        } while (index < list->count);
    }
    return 0xffffffff;
}
