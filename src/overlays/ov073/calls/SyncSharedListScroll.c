#include "nitro/types.h"

typedef struct MenuSharedState {
    s8 selectedIndex;
    u8 pad_01[0xb44 - 1];
    u8 list[4];
} MenuSharedState;

extern MenuSharedState *func_ov039_020bc650(void);
extern int GetPlayerLevelTier(void);
extern void ScrollListWidgetTo(void *list, int value);

void SyncSharedListScroll(void)
{
    MenuSharedState *state = func_ov039_020bc650();
    void *list = state->list;

    if (state->selectedIndex == 4) {
        ScrollListWidgetTo(list, GetPlayerLevelTier());
    }
}
