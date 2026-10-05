#include "nitro/types.h"

typedef struct IdEntry {
    u32 id : 18;
    u32 flags : 6;
    u32 count : 7;
    u32 isSet : 1;
} IdEntry;

typedef struct IdList {
    IdEntry *entries;
    u8 count;
} IdList;

typedef struct PlayerRecords {
    u8 pad_000[0x13c];
    IdList list;
} PlayerRecords;

extern PlayerRecords data_02060b50[];
extern IdEntry *FindEntryById(IdList *list, u32 id);

int GetPlayerEntryCount(int player, u32 id)
{
    IdEntry *entry;

    if (player != 0) {
        return 0;
    }
    entry = FindEntryById(&data_02060b50[player].list, id);
    return entry != NULL ? (u8)entry->count : 0;
}
