#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ScaleSource {
    u32 unk_00_0 : 18;
    u32 kind : 5;
    u32 unk_00_23 : 9;
    u32 unk_04_0 : 16;
    u32 level : 8;
    u32 unk_04_24 : 8;
    u8 pad_08[4];
    u16 divisor;
} ScaleSource;

typedef struct ScaleTarget {
    u8 pad_00[0x30];
    fx32 value;
} ScaleTarget;

extern fx32 FX_Mul(fx32 left, fx32 right);
extern s32 _s32_div_f(s32 dividend, s32 divisor);
extern s64 _ll_mul(s64 a, s64 b);

fx32 ScaleValueByLevelFactor(ScaleSource *source, ScaleTarget *target) {
    fx32 factor;
    u32 level = source->level;

    if (level <= 1) {
        factor = 0x800;
    } else {
        factor = _s32_div_f(level * 0xB34, (u8)source->divisor) + 0x4CC;
        if (source->kind == 3) {
            factor = FX_Mul(factor, 0x1800);
        }
    }
    return (_ll_mul(target->value, factor) + 0x800) >> 12;
}
