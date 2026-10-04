#include "libs/nns/gfd/gfd_LinkedListVramMan_Types.h"

u32 NNS_GfdGetLnkTexVramManagerWorkSize(u32 blockCount)
{
    return blockCount * sizeof(NNSiGfdLnkVramBlock);
}
