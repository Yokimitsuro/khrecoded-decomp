#include "nitro/types.h"

typedef struct SlotMenu {
    s32 state;
} SlotMenu;

extern void SlotMenu_OpenMessagePanel(SlotMenu *menu, int windowType, int arg2, int arg3, int messageId);
extern void *func_ov039_020bc1dc(void);
extern void SetNavigationElementsVisible(void *container, BOOL visible);

void SlotMenu_ShowPointLimitWarning(SlotMenu *menu)
{
    SlotMenu_OpenMessagePanel(menu, 1, 0, 9, 0x5d);
    menu->state = 9;
    SetNavigationElementsVisible(func_ov039_020bc1dc(), FALSE);
}
