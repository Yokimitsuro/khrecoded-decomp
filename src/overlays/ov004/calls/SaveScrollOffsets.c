#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    s16 x;
    s16 y;
} ScrollOffset;

typedef struct {
    u8 pad_00[0x10944];
    ScrollOffset mainScroll;
    ScrollOffset mainPrevScroll;
    u8 pad_1094c[0x21284 - 0x1094c];
    ScrollOffset subScroll;
    ScrollOffset subPrevScroll;
    u8 pad_2128c[0x23aac - 0x2128c];
    fx32 rollPosition;
    fx32 lastRollPosition;
    fx32 prevRollPosition;
} ScrollTextWork;

typedef struct {
    u32 frameCount;
    ScrollTextWork *work;
} ScrollTextGlobals;

extern ScrollTextGlobals data_ov004_020645a0;

void SaveScrollOffsets(void)
{
    data_ov004_020645a0.work->prevRollPosition = data_ov004_020645a0.work->rollPosition;
    data_ov004_020645a0.work->mainPrevScroll.x = data_ov004_020645a0.work->mainScroll.x;
    data_ov004_020645a0.work->mainPrevScroll.y = data_ov004_020645a0.work->mainScroll.y;
    data_ov004_020645a0.work->subPrevScroll.x = data_ov004_020645a0.work->subScroll.x;
    data_ov004_020645a0.work->subPrevScroll.y = data_ov004_020645a0.work->subScroll.y;
}
