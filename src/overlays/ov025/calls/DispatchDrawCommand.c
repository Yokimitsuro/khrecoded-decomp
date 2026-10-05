#include "nitro/types.h"

extern void NNS_GfdRegisterNewVramTransferTask(u32 a, u32 b, u32 c, u32 d);
extern void DC_FlushRange(const void *addr, u32 size);
extern void GXS_LoadBGPltt(void *addr, u32 arg1, u32 size);

void DispatchDrawCommand(u32 entity, int mode) {
    if (mode != 0) {
        DC_FlushRange((void *)(entity + 0x10), 0x60);
        GXS_LoadBGPltt((void *)(entity + 0x10), 0xa0, 0x60);
        return;
    }
    NNS_GfdRegisterNewVramTransferTask(0x1f, 0xa0, entity + 0x10, 0x60);
}
