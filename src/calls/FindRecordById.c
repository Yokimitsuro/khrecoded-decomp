#include "nitro/types.h"

typedef struct {
    u16 id;
    u8 pad_02[14];
} IdRecord;

typedef struct {
    u8 pad_00[0x28];
    IdRecord *idTable;
} RecordManager;

extern RecordManager *data_020613d0;

/* Finds an id-table entry by id. */
IdRecord *FindRecordById(u32 id)
{
    RecordManager *manager = data_020613d0;
    IdRecord *entry;
    int index;

    entry = manager->idTable;
    if ((manager == 0) || (entry == 0)) {
        return 0;
    }
    index = 0;
    do {
        if (entry->id == id) break;
        index = index + 1;
        entry = entry + 1;
    } while (index < 0xb);
    if (index == 0xb) {
        entry = 0;
    }
    return entry;
}
