#include "libs/nns/gfd/gfd_LinkedListVramMan_Types.h"

void NNS_GfdInitLnkPlttVramManager(u32 size, void *work, u32 workSize, BOOL useAsDefault)
{
    sLnkPlttVramManager.size = size;
    sLnkPlttVramManager.work = work;
    sLnkPlttVramManager.workSize = workSize;

    NNS_GfdResetLnkPlttVramState();

    if (useAsDefault) {
        sDefaultAllocPlttVramFunc = NNS_GfdAllocLnkPlttVram;
        sDefaultFreePlttVramFunc = NNS_GfdFreeLnkPlttVram;
    }
}
