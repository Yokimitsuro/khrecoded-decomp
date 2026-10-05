#include "nitro/types.h"

typedef struct PoolParams {
    u32 words[5];
} PoolParams;

typedef struct ParamOwner {
    u8 pad_000[0x174];
    PoolParams params[4];
} ParamOwner;

extern PoolParams gPoolValueHandlers;
extern PoolParams gPoolMotionHandlers;
extern PoolParams data_ov017_020a5e5c;
extern void MIi_CpuCopy32(const void *src, void *dest, u32 size);

void ResetPoolDefaultParams(ParamOwner *owner)
{
    PoolParams first = gPoolValueHandlers;
    PoolParams second = gPoolMotionHandlers;
    PoolParams third = {0};
    PoolParams fourth = data_ov017_020a5e5c;

    MIi_CpuCopy32(&first, &owner->params[0], sizeof(PoolParams));
    MIi_CpuCopy32(&second, &owner->params[1], sizeof(PoolParams));
    MIi_CpuCopy32(&third, &owner->params[2], sizeof(PoolParams));
    MIi_CpuCopy32(&fourth, &owner->params[3], sizeof(PoolParams));
}
