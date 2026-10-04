#include "libs/nns/gfd/gfd_LinkedListVramMan_Types.h"

int NNS_GfdFreeLnkTexVram(NNSGfdTexKey key)
{
    BOOL result;
    const u32 address = (key & 0xffff) << 3;
    const u32 size = ((key & 0x7fff0000) >> 16) << 4;
    const BOOL compressed = (key & 0x80000000) >> 31;

    if (size != 0) {
        if (compressed) {
            result = NNSi_GfdFreeLnkVram(&sLnkTexVramManager.compressedManager,
                                         &sLnkTexVramManager.blockPoolList,
                                         address,
                                         size);
        } else {
            result = NNSi_GfdFreeLnkVram(&sLnkTexVramManager.normalManager,
                                         &sLnkTexVramManager.blockPoolList,
                                         address,
                                         size);
        }

        if (result) {
            return 0;
        } else {
            return 1;
        }
    }
    return 2;
}
