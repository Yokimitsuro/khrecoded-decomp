#include "nitro/types.h"

typedef struct RecordTable RecordTable;

typedef struct {
    u8 pad_00[0x18d9c];
    RecordTable *auxTable;
} StageManager;

extern StageManager *data_ov001_020a0528;

extern void *func_ov001_0208f280(RecordTable *table, u32 id);

void *GetStageAuxRecord(u32 id)
{
    if (data_ov001_020a0528 != 0) {
        return func_ov001_0208f280(data_ov001_020a0528->auxTable, id);
    }
    return 0;
}
