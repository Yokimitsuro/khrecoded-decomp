#include "nitro/types.h"
#include "nitro/fx_types.h"

extern u16 Math_AsinIdx(fx32 value);

fx32 AsinToRadians(const fx32 *value) {
    return (fx32)((s64)Math_AsinIdx(*value) * 0x6488 / 0x10000);
}
