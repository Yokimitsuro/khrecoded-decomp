#include "nitro/types.h"

typedef struct MenuSharedState {
    s8 selectedIndex;
} MenuSharedState;

extern MenuSharedState *func_ov039_020bc650(void);

int GetSharedSelectedIndex(void)
{
    MenuSharedState *state = func_ov039_020bc650();

    if (state != NULL) {
        return state->selectedIndex;
    }
    return 0;
}
