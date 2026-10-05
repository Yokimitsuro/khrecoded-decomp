#include "nitro/types.h"

typedef struct {
    s16 key1;
    s16 key2;
    s16 value;
} PairEntry;

/* Search a 4-entry key pair table. */
s32 LookupPairValue(PairEntry *table, s32 key1, s32 key2)
{
    s32 i;

    for (i = 0; i < 4; i++) {
        if (key1 == table[i].key1 && key2 == table[i].key2) {
            return table[i].value;
        }
    }
    return -1;
}
