#include "nitro/types.h"

typedef struct MenuSharedState {
    u8 pad_000[0xc84];
    u32 messages;
} MenuSharedState;

extern MenuSharedState *func_ov039_020bc650(void);

u32 MakeSharedMessageKey(u32 index)
{
    MenuSharedState *state = func_ov039_020bc650();

    return ((((state->messages + 0x8000) & 0xfffffc) << 7) | 0x80000000) | (index & 0x1ff);
}
