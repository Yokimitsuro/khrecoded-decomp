#include "nitro/types.h"

typedef struct StageLayout {
    u8 pad_000[0x13d14];
    u8 smallRecords[1];
} StageLayout;

extern StageLayout *data_ov001_020a0528;
extern u32 _u32_div_f(u32 numerator, u32 denominator);

u16 GetSmallRecordIndex(u8 *record)
{
    return _u32_div_f(record - data_ov001_020a0528->smallRecords, 0x1c) + 1;
}
