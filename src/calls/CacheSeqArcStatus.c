#include "nitro/types.h"

extern u8 *data_0206084c;
extern u32 NNS_SndHeapSaveState(u32 value);

int CacheSeqArcStatus(int index)
{
    u8 *ctx = data_0206084c;
    u32 status = NNS_SndHeapSaveState(*(u32 *)(data_0206084c + 0xb04b4));
    *(u32 *)(ctx + index * 4 + 0xa8) = status;
    return (int)(s8)status;
}
