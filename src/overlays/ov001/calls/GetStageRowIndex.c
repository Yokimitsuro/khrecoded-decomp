#include "nitro/types.h"

typedef struct StageLayout {
    u8 pad_000[0x210];
    int baseOffset;
} StageLayout;

extern StageLayout *data_ov001_020a0528;
extern u32 _u32_div_f(u32 numerator, u32 denominator);

u16 GetStageRowIndex(int offset)
{
    return _u32_div_f(offset - data_ov001_020a0528->baseOffset, 0x1c8) + 1;
}
