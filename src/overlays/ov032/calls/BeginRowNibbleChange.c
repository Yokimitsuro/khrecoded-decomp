#include "nitro/types.h"

typedef struct {
    int header;
    u32 current : 4;
    u32 target : 4;
    u8 pad_08[0x1d8];
} RowEntry;

typedef struct {
    u8 pad_00[0xcc];
    RowEntry *rows;
} RowOwner;

extern BOOL HasPendingNibbleChange(RowEntry *row);
extern int func_ov032_020bbf40(RowOwner *owner, int index);

BOOL BeginRowNibbleChange(RowOwner *owner, int index)
{
    RowEntry *row = &owner->rows[index];
    if (HasPendingNibbleChange(row) == FALSE) {
        row->target = func_ov032_020bbf40(owner, index);
        return TRUE;
    }
    return FALSE;
}
