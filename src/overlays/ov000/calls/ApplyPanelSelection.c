#include "nitro/types.h"

typedef struct {
    u8 pad_00[0x28];
    u32 active;
    u32 selection;
} Panel;

extern void func_ov000_02061a80(Panel *panel, u32 mode);
extern int func_0202b5e8(void);

void ApplyPanelSelection(Panel *panel)
{
    u32 mode;

    switch (panel->selection) {
    case 0:
        mode = 0;
        break;
    case 1:
        mode = 1;
        break;
    case 2:
        mode = 2;
        break;
    case 3:
        mode = 3;
        break;
    default:
        mode = 0;
        break;
    }
    func_ov000_02061a80(panel, mode);
    panel->active = 1;
    func_0202b5e8();
}
