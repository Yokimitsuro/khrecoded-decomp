#include "nitro/types.h"

typedef struct MenuPanel {
    void (*onChange)(void);
    u8 pad_04[0x6c];
    int slots[3];
    u8 mode;
} MenuPanel;

extern void func_ov025_020b65e4(MenuPanel *panel, int startSlot, int *slots);

void ApplyModeAndNotify(MenuPanel *panel, u8 mode)
{
    int saved[3] = {0, 0, 0};
    int i;

    panel->mode = mode;
    for (i = 0; i < 3; i++) {
        saved[i] = panel->slots[i];
    }
    func_ov025_020b65e4(panel, 0, saved);
    if (panel->onChange != NULL) {
        panel->onChange();
    }
}
