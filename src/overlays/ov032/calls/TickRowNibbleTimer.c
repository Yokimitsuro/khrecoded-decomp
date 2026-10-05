#include "nitro/types.h"

typedef struct {
    u8 pad_00[8];
    u32 paused : 1;
    u8 pad_0c[0xa];
    u16 timer;
    u8 pad_18[0x1c8];
} RowEntry;

typedef struct {
    u8 pad_00[0xcc];
    RowEntry *rows;
} RowOwner;

extern s32 func_ov032_020bbc44(void *owner, s32 index);
extern BOOL BeginRowNibbleChange(RowOwner *owner, int index);

void TickRowNibbleTimer(RowOwner *owner, int index)
{
    RowEntry *row = &owner->rows[index];
    if (row->paused == 0) {
        if (row->timer >= func_ov032_020bbc44(owner, index)) {
            if (BeginRowNibbleChange(owner, index)) {
                row->timer = 0;
            }
        } else {
            row->timer++;
        }
    }
}
