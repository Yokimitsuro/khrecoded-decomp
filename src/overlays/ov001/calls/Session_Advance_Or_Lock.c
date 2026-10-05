#include "nitro/types.h"

extern u32 data_ov001_020a0480;
extern s32 PopSessionQueue(u32 fieldAddr);
extern u32 ReleaseSessionHandle();
extern u32 FlushPendingEntryRefresh();

s32 Session_Advance_Or_Lock(void) {
    u32 base = data_ov001_020a0480;
    s32 result = -1;
    s32 status = PopSessionQueue(data_ov001_020a0480 + 0x24);

    switch (status) {
    case 0:
        *(u8 *)(data_ov001_020a0480 + 0x1b) = 1;
        result = 8;
        break;
    case 1:
        ReleaseSessionHandle(base, 1);
        FlushPendingEntryRefresh();
        result = 4;
        break;
    }
    return result;
}
