#include "nitro/types.h"

typedef struct StageEntry {
    u8 data[8];
} StageEntry;

typedef struct StageTable {
    u8 pad_00[8];
    StageEntry entries[64];
} StageTable;

extern StageTable *data_ov001_020a0528;

StageEntry *GetStageEntry(int id)
{
    int index = id - 1;
    StageTable *table = data_ov001_020a0528;

    if (table == NULL) {
        return NULL;
    }
    if (index < 0) {
        return NULL;
    }
    if (index < 64) {
        return &table->entries[index];
    }
    return NULL;
}
