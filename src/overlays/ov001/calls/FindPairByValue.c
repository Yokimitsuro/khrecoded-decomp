#include "nitro/types.h"

typedef struct KeyValuePair {
    u16 value;
    u16 key;
} KeyValuePair;

typedef struct PairTable {
    u8 pad_000[8];
    KeyValuePair pairs[64];
    u8 count;
} PairTable;

extern PairTable *data_ov001_020a0490;

KeyValuePair *FindPairByValue(u16 value)
{
    PairTable *table = data_ov001_020a0490;
    int i;

    for (i = 0; i < table->count; i++) {
        if (value == table->pairs[i].value) {
            return &table->pairs[i];
        }
    }
    return NULL;
}
