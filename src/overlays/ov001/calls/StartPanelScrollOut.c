#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct ScrollPanel {
    int state;
    u8 pad_004[0x130];
    fx32 scrollY;
} ScrollPanel;

extern ScrollPanel *data_ov001_020a04ec;
extern void StartCountdownTimer(int arg, int mode);
extern void func_ov001_0207d238(int mode);

BOOL StartPanelScrollOut(int arg)
{
    ScrollPanel *panel = data_ov001_020a04ec;

    if (panel != NULL) {
        StartCountdownTimer(arg, 0);
        panel->scrollY += 0x9a000;
        func_ov001_0207d238(0);
        panel->state = 3;
    }
    return panel != NULL;
}
