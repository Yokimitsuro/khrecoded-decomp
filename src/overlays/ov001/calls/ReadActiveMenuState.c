#include "nitro/types.h"

typedef struct MenuContext {
    u32 unk_00;
    u8 state[4];
} MenuContext;

extern MenuContext *data_ov001_020a04a4;
extern void ResolveWaitTarget(void *state, u8 *out);

void ReadActiveMenuState(u8 *out)
{
    if (data_ov001_020a04a4 == NULL) {
        *out = 0;
        return;
    }
    ResolveWaitTarget(data_ov001_020a04a4->state, out);
}
