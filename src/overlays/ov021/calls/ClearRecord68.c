#include "nitro/types.h"

typedef struct Record68 {
    u8 pad_00[0x54];
    int slot54;
    int slot58;
    int slot5c;
    u8 pad_60[8];
} Record68;

extern void MI_CpuFill8(void *dst, int value, int size);

void ClearRecord68(Record68 *record)
{
    MI_CpuFill8(record, 0, sizeof(Record68));
    record->slot54 = 0;
    record->slot5c = 0;
    record->slot58 = 0;
}
