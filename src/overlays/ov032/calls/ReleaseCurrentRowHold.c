#include "nitro/types.h"

typedef struct {
    int header;
    u32 current : 4;
    u32 target : 4;
    u32 : 24;
    u32 paused : 1;
    u8 pad_0c[0xe];
    s16 holdFrames;
} RowEntry;

extern u8 *func_ov032_020bbc98(void *group);
extern RowEntry *func_ov032_020bbc80(void *group);
extern void SetGroupFormation(void *group);

void ReleaseCurrentRowHold(void *group)
{
    RowEntry *row;
    u32 target;
    BOOL expired;

    func_ov032_020bbc98(group);
    row = func_ov032_020bbc80(group);
    target = row->target;
    expired = FALSE;
    row->paused = 0;
    if (row->holdFrames >= 60) {
        target = 3;
        expired = TRUE;
    }
    if (row->current != target || expired) {
        SetGroupFormation(group);
    }
}
