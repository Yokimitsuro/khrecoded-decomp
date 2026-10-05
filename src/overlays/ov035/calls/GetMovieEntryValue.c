#include "nitro/types.h"

typedef struct MovieEntry {
    u8 unk_00;
    u8 kind : 7;
    u8 flag : 1;
    s16 value;
    u8 pad_04[0x18];
} MovieEntry;

typedef struct MovieContext {
    u8 pad_00[0x42];
    u8 entryCount;
    u8 pad_43[0xd];
    MovieEntry *entries;
} MovieContext;

extern MovieContext *data_ov035_020bc500;

s16 GetMovieEntryValue(int index)
{
    MovieEntry *entry;

    if (index >= 0 && index < data_ov035_020bc500->entryCount) {
        entry = &data_ov035_020bc500->entries[index];
        if (entry != NULL) {
            return entry->value;
        }
    }
    return -1;
}