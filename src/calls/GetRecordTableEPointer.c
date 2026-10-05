#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x70];
    void *tableE;
} RecordManager;

extern RecordManager *gRecordManager;

/* Gets record table E's pointer. */
void *GetRecordTableEPointer(void)
{
    RecordManager *manager = gRecordManager;

    if (manager == 0) {
        return 0;
    }
    return manager->tableE;
}
