#include "libs/nns/gfd/gfd_LinkedListVramMan_Types.h"

void NNS_GfdInitLnkTexVramManager(u32 size, u32 compressedSize, void *work, u32 workSize, BOOL useAsDefault)
{
    sLnkTexVramManager.size = size;
    sLnkTexVramManager.compressedSize = compressedSize;
    sLnkTexVramManager.work = work;
    sLnkTexVramManager.workSize = workSize;

    NNS_GfdResetLnkTexVramState();

    if (useAsDefault) {
        sDefaultAllocTexVramFunc = NNS_GfdAllocLnkTexVram;
        sDefaultFreeTexVramFunc = NNS_GfdFreeLnkTexVram;
    }
}
