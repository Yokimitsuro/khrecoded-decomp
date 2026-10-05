#include "nitro/types.h"

typedef struct ResourceContainer ResourceContainer;

typedef struct StatusMenu {
    u8 pad_0000[0x10e0];
    ResourceContainer *container;
} StatusMenu;

typedef struct StatusPanel {
    u8 pad_00[0xe4];
    void *element;
} StatusPanel;

extern void func_ov027_020b95a0(ResourceContainer *container, void *element, BOOL visible);

void HideStatusPanelElement(StatusMenu *menu, StatusPanel *panel)
{
    func_ov027_020b95a0(menu->container, panel->element, FALSE);
}
