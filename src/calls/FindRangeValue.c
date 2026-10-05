#include "nitro/types.h"

typedef struct RangeEntry {
    int unk_00;
    int major;
    int minor;
    int value;
} RangeEntry;

typedef struct RangeTables {
    u8 pad_00[0x34];
    RangeEntry *ranges;
} RangeTables;

extern RangeTables *gRecordManager;

int FindRangeValue(int major, int minor)
{
    RangeTables *tables = gRecordManager;
    int i;
    RangeEntry *entry;
    int result = -1;
    RangeEntry *ranges;

    if (tables == NULL || (ranges = tables->ranges) == NULL) {
        return -1;
    }
    for (i = 0; i < 333; i++) {
        entry = &ranges[i];
        if (entry->major < major) {
            continue;
        }
        if (entry->major > major) {
            break;
        }
        if (entry->minor < minor) {
            continue;
        }
        if (entry->minor > minor) {
            break;
        }
        result = entry->value;
        break;
    }
    return result;
}
