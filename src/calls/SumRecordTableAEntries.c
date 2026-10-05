#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x40];
    u16 *tableA;
} RecordManager;

extern RecordManager *data_020613d0;

/* Sums record table A entries. */
u16 SumRecordTableAEntries(int count)
{
    RecordManager *manager = data_020613d0;
    int i;
    u16 sum = 0;

    for (i = 0; i < count; i++) {
        sum = sum + manager->tableA[i];
    }
    return sum;
}
