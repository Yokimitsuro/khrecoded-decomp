#include "nitro/types.h"
#include "nitro/fx_types.h"

extern void func_ov001_02080a38(void *anim, fx32 frame);

BOOL AdvanceAnimFrame_02080a60(void *anim, fx32 step, BOOL loop, fx32 length, fx32 *frame)
{
    BOOL finished;

    length -= 0x1000;
    finished = FALSE;
    if (length <= *frame) {
        if (loop) {
            *frame -= length;
        } else {
            *frame = length;
            finished = TRUE;
        }
    }
    func_ov001_02080a38(anim, *frame);
    if (!finished) {
        *frame += step;
    }
    return !finished;
}
