#include "nitro/types.h"

typedef struct {
    u8 pad_00[4];
    u32 low : 16;
    u32 state : 8;
    u8 pad_08[8];
    u16 counter;
    u8 pad_12[0x1ce];
} RowEntry;

typedef struct {
    u8 pad_00[0xcc];
    RowEntry *rows;
} RowOwner;

extern s32 GetRowRespawnLimit(void *owner, s32 index);

void AdvanceRowCounter(RowOwner *owner, int index)
{
    RowEntry *row = &owner->rows[index];
    if (row->state <= 3) {
        if (row->counter < GetRowRespawnLimit(owner, index)) {
            row->counter++;
        }
    } else {
        row->counter = 0;
    }
}
