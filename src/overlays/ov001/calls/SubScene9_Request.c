#include "nitro/types.h"

extern u32 data_ov001_020a0488;
extern s32 func_ov001_02066e70(void);

u32 SubScene9_Request(u8 value)
{
    u8 *state;
    s32 busy;

    state = (u8 *)data_ov001_020a0488;
    busy = func_ov001_02066e70();
    if (busy == 0) {
        state[1] = value;
        *state = 1;
        return 1;
    }
    return 0;
}
