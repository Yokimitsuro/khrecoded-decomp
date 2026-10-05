#include "nitro/types.h"

typedef struct ValueTriple {
    s16 values[3];
} ValueTriple;

typedef struct TripleList {
    s16 count;
    ValueTriple items[1];
} TripleList;

typedef struct ValueEntries {
    void *first[9];
    TripleList *second[8];
} ValueEntries;

typedef struct ValueTables {
    u8 pad_00[0x38];
    ValueEntries *entries;
} ValueTables;

extern ValueTables *gRecordManager;

s16 *GetSecondTableTriple(int index, int position)
{
    ValueTables *tables = gRecordManager;
    TripleList *list;

    if (index >= 0 && index < 8) {
        list = tables->entries->second[index];
        if (position < list->count) {
            return list->items[position].values;
        }
    }
    return NULL;
}
