#include "nitro/types.h"

typedef struct ValueTables {
    u8 pad_00[0x38];
    s16 **entries;
} ValueTables;

extern ValueTables *gRecordManager;

s16 *GetTableEntryElement(int index, int position)
{
    ValueTables *tables = gRecordManager;
    s16 *entry;

    if (index >= 0 && index < 9) {
        entry = tables->entries[index];
        if (position < entry[0]) {
            return entry + 1 + position;
        }
    }
    return NULL;
}
