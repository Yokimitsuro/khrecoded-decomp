#include "nitro/types.h"

typedef struct {
    u8 pad_00[8];
    u32 low : 16;
    u32 step : 6;
    u8 pad_0c[0x1d4];
} RowEntry;

typedef struct {
    u8 pad_00[0xcc];
    RowEntry *rows;
} RowOwner;

typedef struct {
    u8 pad_00[0x10];
    u8 sequence[11];
} RowDefinition;

extern RowDefinition *GetRowDefinition(void *owner, s32 index);

void AdvanceRowSequenceStep(RowOwner *owner, int index)
{
    RowEntry *row = &owner->rows[index];
    RowDefinition *definition = GetRowDefinition(owner, index);
    row->step++;
    if (row->step >= 11 || definition->sequence[row->step] == 11) {
        row->step = 0;
    }
}
