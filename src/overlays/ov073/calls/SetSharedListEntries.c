#include "nitro/types.h"

typedef struct MenuSharedState {
    s8 selectedIndex;
    u8 pad_01[0xb44 - 1];
    u8 list[4];
} MenuSharedState;

extern MenuSharedState *func_ov039_020bc650(void);
extern void SetListWidgetEntries(void *list, const u16 *ids);

void SetSharedListEntries(const u16 *ids)
{
    MenuSharedState *state = func_ov039_020bc650();
    void *list = state->list;

    if (state->selectedIndex == 4) {
        SetListWidgetEntries(list, ids);
    }
}
