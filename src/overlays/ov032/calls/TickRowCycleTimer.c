#include "nitro/types.h"

typedef struct {
    u8 pad_00[8];
    u32 bit0 : 1;
    u32 frozen : 1;
    u32 reset : 1;
    u8 pad_0c[6];
    u16 timer;
    u8 pad_14[0x1cc];
} RowEntry;

typedef struct {
    u8 pad_00[0xcc];
    RowEntry *rows;
} RowOwner;

extern s32 func_ov032_020bbc2c(void *owner, s32 index);
extern void QueueFieldObjectModeChange(RowOwner *owner, int index, int arg);

void TickRowCycleTimer(RowOwner *owner, int index)
{
    RowEntry *row = &owner->rows[index];
    if (row->reset) {
        row->timer = 0;
        return;
    }
    if (row->frozen == 0) {
        if (row->timer >= func_ov032_020bbc2c(owner, index)) {
            QueueFieldObjectModeChange(owner, index, 0);
            row->timer = 0;
        } else {
            row->timer++;
        }
    }
}
