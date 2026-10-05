#include "nitro/types.h"

typedef struct {
    union {
        u32 value;
        struct {
            u16 first;
            u16 second;
        } pair;
    } key;
    s32 kind;
} ListEntry;

typedef struct {
    u8 pad_000[0x60];
    ListEntry entries[24];
    u8 count;
} EntryList;

u32 EntryList_FindByFirstId(EntryList *list, u32 id)
{
    u32 index;
    u32 count = list->count;

    for (index = 0; index < count; index = (u8)(index + 1)) {
        if (list->entries[index].kind == 2 && id == list->entries[index].key.pair.first) {
            return index;
        }
    }
    return 0xffffffff;
}
