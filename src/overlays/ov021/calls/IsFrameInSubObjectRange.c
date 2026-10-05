#include "nitro/types.h"

typedef struct FrameRange {
    s32 pad0[2];
    s32 start;
    s32 end;
} FrameRange;

extern FrameRange *SelectSubObject(void *obj, s32 which);

BOOL IsFrameInSubObjectRange(void *obj, s32 frame, s32 which)
{
    BOOL inRange = FALSE;
    FrameRange *range = SelectSubObject(obj, which);
    s32 start = range->start;
    s32 end = range->end;
    if (end == -0x1000) {
        end = 0x7fffffff;
    }
    if (start <= frame && frame < end) {
        inRange = TRUE;
    }
    return inRange;
}
