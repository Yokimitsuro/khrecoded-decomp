#include "nitro/types.h"

typedef struct StageLayout {
    u8 pad_000[0x4b14];
    u8 largeRecords[1];
} StageLayout;

extern StageLayout *data_ov001_020a0528;
extern u32 _u32_div_f(u32 numerator, u32 denominator);

u16 GetLargeRecordIndex(u8 *record)
{
    return _u32_div_f(record - data_ov001_020a0528->largeRecords, 0x3c8) + 1;
}
