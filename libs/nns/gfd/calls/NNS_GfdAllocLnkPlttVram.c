#include "libs/nns/gfd/gfd_LinkedListVramMan_Types.h"

NNSGfdPlttKey NNS_GfdAllocLnkPlttVram(u32 size, BOOL fourColor, u32 option)
{
    u32 address;
    BOOL result;

    size = GfdRoundupPlttSize_(size);
    if (size >= 0x7fff8) {
        return 0;
    }

    if (fourColor) {
        result = NNSi_GfdAllocLnkVramAligned(&sLnkPlttVramManager.manager,
                                             &sLnkPlttVramManager.blockPoolList,
                                             &address,
                                             size,
                                             8);
        if (address + size > 0x10000) {
            if (!NNSi_GfdFreeLnkVram(&sLnkPlttVramManager.manager,
                                     &sLnkPlttVramManager.blockPoolList,
                                     address,
                                     size)) {
            }
            return 0;
        }
    } else {
        result = NNSi_GfdAllocLnkVramAligned(&sLnkPlttVramManager.manager,
                                             &sLnkPlttVramManager.blockPoolList,
                                             &address,
                                             size,
                                             0x10);
    }

    if (result) {
        return ((size >> 3) << 16) | (0xffff & (address >> 3));
    }
    return 0;
}
