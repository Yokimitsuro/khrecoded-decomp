#include "nitro/types.h"

typedef struct {
    u32 pad_bits : 18;
    u32 phase : 5;
    u32 targetPhase : 5;
    u32 high : 4;
    u32 mode : 4;
    u8 pad_08[0x1d8];
} RowEntry;

typedef struct {
    u8 pad_00[0xcc];
    RowEntry *rows;
} RowOwner;

BOOL IsRowSettledInMode5(RowOwner *owner, int index)
{
    RowEntry *row = &owner->rows[index];
    if (row->mode == 5 && row->phase != 3 && row->phase == row->targetPhase) {
        return TRUE;
    }
    return FALSE;
}
