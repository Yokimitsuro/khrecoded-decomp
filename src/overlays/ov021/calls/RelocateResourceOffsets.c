#include "nitro/types.h"

typedef struct ResEntry {
    u32 pad0[2];
    u8 *data;
} ResEntry;

typedef struct ResHeader {
    s32 count;
    ResEntry *entries;
    u8 *dataBase;
    u8 *extra;
} ResHeader;

void RelocateResourceOffsets(ResHeader *header)
{
    ResEntry *entry;
    int i;

    entry = (ResEntry *)((u8 *)header + (u32)header->entries);
    header->dataBase = (u8 *)header + (u32)header->dataBase;
    header->extra = (u8 *)header + (u32)header->extra;
    header->entries = entry;
    for (i = 0; i < header->count; i++) {
        entry->data = header->dataBase + (u32)entry->data;
        entry++;
    }
}
