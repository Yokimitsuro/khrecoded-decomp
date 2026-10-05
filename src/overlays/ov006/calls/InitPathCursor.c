#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 active;
    u8 unk_01;
    u8 pad_02;
    u8 unk_03;
    u8 pad_04[0x10];
    s32 progress;
    u8 pad_18[4];
    VecFx32 start;
    VecFx32 end;
    VecFx32 current;
} PathCursor;

void InitPathCursor(PathCursor *cursor, const VecFx32 *start, const VecFx32 *end) {
    cursor->active = 1;
    cursor->start = *start;
    cursor->end = *end;
    cursor->current = *start;
    cursor->unk_01 = 0;
    cursor->unk_03 = 0;
    cursor->progress = 0;
}
