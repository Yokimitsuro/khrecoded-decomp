#include "nitro/types.h"

typedef struct {
    u8 pad_00[8];
    s32 delta;
} DeltaRecord;

BOOL IsDeltaBeyond16(u32 unused, DeltaRecord *record)
{
    s32 delta = record->delta;

    if (delta < 0) {
        delta = -delta;
    }
    if (0x10 < delta) {
        return 1;
    }
    return 0;
}
