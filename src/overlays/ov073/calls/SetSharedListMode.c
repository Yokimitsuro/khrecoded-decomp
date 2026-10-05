#include "nitro/types.h"

typedef struct MenuSharedState {
    s8 selectedIndex;
    u8 pad_01[0xb44 - 1];
    u8 list[4];
} MenuSharedState;

extern MenuSharedState *func_ov039_020bc650(void);
extern void func_ov073_020c3f54(void *list, u8 mode);

void SetSharedListMode(int mode)
{
    MenuSharedState *state = func_ov039_020bc650();
    void *list = state->list;

    if (state->selectedIndex == 4) {
        func_ov073_020c3f54(list, mode);
    }
}
