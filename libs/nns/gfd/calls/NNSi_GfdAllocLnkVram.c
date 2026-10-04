#include "libs/nns/gfd/gfdi_LinkedListVramMan_Common.h"

extern BOOL NNSi_GfdAllocLnkVramAligned(NNSiGfdLnkVramMan *, NNSiGfdLnkVramBlock **, u32 *, u32, u32);

BOOL NNSi_GfdAllocLnkVram(NNSiGfdLnkVramMan *manager, NNSiGfdLnkVramBlock **blockPoolList, u32 *resultAddress, u32 size)
{
    return NNSi_GfdAllocLnkVramAligned(manager, blockPoolList, resultAddress, size, 0);
}
