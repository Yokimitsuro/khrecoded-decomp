#include "nitro/types.h"

typedef struct PairScreen {
    u8 pad_00[0x06];
    u8 order;
    u8 pad_07[0x1D0 - 0x07];
    void *layout;
    u8 pad_1D4[0x208 - 0x1D4];
    void *widgets[2];
} PairScreen;

extern s32 *func_ov027_020b91c8(void *layout, void *widget);
extern void func_ov027_020b91e8(void *layout, void *widget, s32 *position, s32 mode);

void ArrangeWidgetPair(PairScreen *screen) {
    s32 *positions[2];

    positions[0] = func_ov027_020b91c8(screen->layout, screen->widgets[0]);
    positions[1] = func_ov027_020b91c8(screen->layout, screen->widgets[1]);
    func_ov027_020b91e8(screen->layout, screen->widgets[0], positions[screen->order ^ 1], 0);
    func_ov027_020b91e8(screen->layout, screen->widgets[1], positions[screen->order], 0);
}
