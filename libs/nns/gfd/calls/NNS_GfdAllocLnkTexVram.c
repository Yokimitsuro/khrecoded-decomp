#include "libs/nns/gfd/gfd_LinkedListVramMan_Types.h"

NNSGfdTexKey NNS_GfdAllocLnkTexVram(u32 size, BOOL compressed, u32 option)
{
    u32 address;
    BOOL result;

    size = GfdRoundupTexSize_(size);
    if (size >= 0x7fff0) {
        return 0;
    }

    if (compressed) {
        result = NNSi_GfdAllocLnkVram(&sLnkTexVramManager.compressedManager,
                                      &sLnkTexVramManager.blockPoolList,
                                      &address,
                                      size);
    } else {
        result = NNSi_GfdAllocLnkVram(&sLnkTexVramManager.normalManager,
                                      &sLnkTexVramManager.blockPoolList,
                                      &address,
                                      size);
    }

    if (result) {
        return ((size >> 4) << 16) | (0xffff & (address >> 3)) | compressed << 31;
    }
    return 0;
}
