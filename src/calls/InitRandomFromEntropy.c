#include "nitro/types.h"

typedef struct RandContext32 {
    u32 x;
    u32 mul;
    u32 add;
} RandContext32;

typedef struct RandContext64 {
    u64 x;
    u64 mul;
    u64 add;
} RandContext64;

extern RandContext32 data_020604d8;
extern RandContext64 data_020604e4;
extern void OS_GetLowEntropyData(u32 *buffer);

static inline void InitRand64(RandContext64 *context, u64 seed)
{
    context->x = seed;
    context->mul = 0x5d588b656c078965ULL;
    context->add = 0x269ec3;
}

static inline void InitRand32(RandContext32 *context, u32 seed)
{
    context->x = seed;
    context->mul = 0x5d588b65;
    context->add = 0x269ec3;
}

void InitRandomFromEntropy(void)
{
    u32 entropy[8];
    u32 seed32;
    u64 seed64;
    int i;

    OS_GetLowEntropyData(entropy);
    for (i = 0; i < 8; i++) {
        seed32 ^= entropy[i];
        seed32 = (seed32 >> 5) | (seed32 << 27);
        seed64 ^= entropy[i];
        seed64 = (seed64 >> 9) | ((seed64 & 0x1ff) << 55);
    }
    InitRand64(&data_020604e4, seed64);
    InitRand32(&data_020604d8, seed32);
}
