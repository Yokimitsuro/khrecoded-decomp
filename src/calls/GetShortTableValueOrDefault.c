#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x3c];
    s16 *shortTable;
} RecordManager;

extern RecordManager *gRecordManager;

/* Reads a short table entry, or default. */
signed long GetShortTableValueOrDefault(signed long index)
{
    RecordManager *manager = gRecordManager;
    signed long value;

    value = manager->shortTable[index + 1];
    if (value < 0) {
        value = 0x28;
    }
    return value;
}
