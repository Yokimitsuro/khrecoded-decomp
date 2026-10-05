#include "nitro/types.h"

typedef struct ValueEntries {
    s16 *first[9];
    s16 *second[8];
} ValueEntries;

typedef struct ValueTables {
    u8 pad_00[0x38];
    ValueEntries *entries;
} ValueTables;

extern ValueTables *gRecordManager;

int GetSecondTableEntryValue(int index)
{
    ValueTables *tables = gRecordManager;

    if (index >= 0 && index < 8) {
        return *tables->entries->second[index];
    }
    return 0;
}
