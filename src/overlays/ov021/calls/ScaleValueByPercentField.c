#include "nitro/types.h"

extern s32 _s32_div_f(s32 numerator, s32 denominator);
extern s32 FX_Mul(s32 left, s32 right);

typedef struct {
    u8 pad_000[0x1d4];
    u8 *unk_1d4;
} BigObject;

/* Result is computed but unused. */
void ScaleValueByPercentField(BigObject *obj, s32 value)
{
    s32 fraction = _s32_div_f((u32)*(u16 *)(obj->unk_1d4 + 4) << 0xc, 100);
    FX_Mul(fraction, value);
}
