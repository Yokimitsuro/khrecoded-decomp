#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct Record60 {
    u8 pad_00[0x1c];
    int index;
    u8 pad_20[0x34];
    fx32 scale;
    u8 pad_58[8];
} Record60;

extern void MI_CpuFill8(void *dst, int value, int size);

void InitRecord60(Record60 *record)
{
    MI_CpuFill8(record, 0, sizeof(Record60));
    record->scale = 0x1000;
    record->index = -1;
}
