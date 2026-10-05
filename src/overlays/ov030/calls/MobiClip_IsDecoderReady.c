#include "nitro/types.h"

extern u32 gMobiClipSourceHandle;
extern u32 Obj_GetWord28(u32 handle);

u32 MobiClip_IsDecoderReady(void)
{
    u32 ready;

    ready = Obj_GetWord28(gMobiClipSourceHandle);
    if (ready != 0) {
        return 1;
    }
    return 0;
}
