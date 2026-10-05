#include "nitro/types.h"

typedef struct MenuSharedState MenuSharedState;

extern MenuSharedState *func_ov039_020bc650(void);
extern void func_ov073_020c1c00(MenuSharedState *state, u8 mask);
extern void func_ov073_020c1c70(MenuSharedState *state, u8 mask);

void ToggleSharedStateFlag(BOOL enable)
{
    MenuSharedState *state = func_ov039_020bc650();

    if (enable) {
        func_ov073_020c1c00(state, 1);
    } else {
        func_ov073_020c1c70(state, 1);
    }
}
