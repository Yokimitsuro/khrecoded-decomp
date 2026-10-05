#include "nitro/types.h"

typedef struct SubModeOwner {
    u8 pad_00[6];
    u8 state;
    u8 pad_07[0xd];
    u8 busy;
} SubModeOwner;

extern int func_ov021_020af48c(void);

u8 GetSubModeState(SubModeOwner *owner, BOOL update)
{
    u8 state = owner->state;
    if (update && owner->busy == 0 && func_ov021_020af48c()) {
        state = 0;
    }
    return state;
}
