#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x70];
    void *tableE;
} RecordManager;

extern RecordManager *data_020613d0;

/* Gets record table E's pointer. */
void *GetRecordTableEPointer(void)
{
    RecordManager *manager = data_020613d0;

    if (manager == 0) {
        return 0;
    }
    return manager->tableE;
}
