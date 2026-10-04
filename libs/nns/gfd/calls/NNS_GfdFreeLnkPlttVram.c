#include "libs/nns/gfd/gfd_LinkedListVramMan_Types.h"

int NNS_GfdFreeLnkPlttVram(NNSGfdPlttKey key)
{
    const u32 address = (key & 0xffff) << 3;
    const u32 size = ((key & 0xffff0000) >> 16) << 3;
    const BOOL result = NNSi_GfdFreeLnkVram(&sLnkPlttVramManager.manager,
                                            &sLnkPlttVramManager.blockPoolList,
                                            address,
                                            size);

    if (result) {
        return 0;
    } else {
        return 1;
    }
}
