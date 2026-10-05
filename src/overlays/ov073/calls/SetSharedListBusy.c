#include "nitro/types.h"

typedef struct ResourceContainer ResourceContainer;

typedef struct MenuSharedState {
    s8 selectedIndex;
    u8 pad_0001[0xb44 - 1];
    u8 list[0x10e0 - 0xb44];
    ResourceContainer *container;
} MenuSharedState;

extern MenuSharedState *func_ov039_020bc650(void);
extern BOOL func_ov039_020bc0f4(void);
extern void SetListWidgetBusy(void *list, BOOL busy);
extern void *FindWidgetById(ResourceContainer *container, int id);
extern void SetEntrySlotsVisible(ResourceContainer *container, void *element, BOOL visible);

void SetSharedListBusy(BOOL busy)
{
    MenuSharedState *state = func_ov039_020bc650();
    void *list = state->list;
    BOOL visible;

    if (state->selectedIndex == 4) {
        SetListWidgetBusy(list, busy);
        if (busy == 0 && func_ov039_020bc0f4() == 0) {
            visible = TRUE;
        } else {
            visible = FALSE;
        }
        SetEntrySlotsVisible(state->container, FindWidgetById(state->container, 0xe), visible);
    }
}
