#include "nitro/types.h"

typedef struct PanelOwner {
    u8 pad_000[0x494];
    int scrollSpeed;
} PanelOwner;

typedef struct Panel Panel;

struct Panel {
    u8 pad_00[8];
    PanelOwner *owner;
    u8 pad_0C[0x5c];
    void (*update)(Panel *panel);
    void (*draw)(Panel *panel);
    int state;
};

extern void func_ov001_02085f04(Panel *panel);
extern void SelectPanelItemEntry(Panel *panel);

void SetupPanelHandlers(Panel *panel)
{
    panel->owner->scrollSpeed = 0x1800;
    panel->update = func_ov001_02085f04;
    panel->draw = SelectPanelItemEntry;
    panel->state = 0;
}
