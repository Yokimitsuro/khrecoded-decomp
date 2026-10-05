#include "nitro/types.h"

extern u32 ByteCode_ResolveOperand(void);
extern void SubtitleText_BeginDraw(u32 stream);
extern void func_ov003_02065028(u32 stream, u32 tick);
extern void SubtitleText_FlushUpload(u32 stream);

/* Resets, then catches up, a movie subtitle stream. */
u32 ResyncMovieSubtitleStream(int context)
{
    u32 tick;

    tick = ByteCode_ResolveOperand();
    SubtitleText_BeginDraw(**(u32 **)(context + 0x1c8));
    func_ov003_02065028(**(u32 **)(context + 0x1c8), tick);
    SubtitleText_FlushUpload(**(u32 **)(context + 0x1c8));
    return 1;
}
