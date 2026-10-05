#include "nitro/types.h"

typedef struct ResourceContainer ResourceContainer;

typedef struct StatusMenu {
    u8 pad_0000[0x10e0];
    ResourceContainer *container;
} StatusMenu;

typedef struct StatusScreen {
    u8 pad_000[0x808];
    void *element;
} StatusScreen;

extern void SetEntrySlotsVisible(ResourceContainer *container, void *element, BOOL visible);

void HideStatusScreenElement(StatusMenu *menu, StatusScreen *screen)
{
    SetEntrySlotsVisible(menu->container, screen->element, FALSE);
}
