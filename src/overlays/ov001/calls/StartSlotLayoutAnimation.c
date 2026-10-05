#include "nitro/types.h"

typedef struct LayoutNode {
    u8 data[0x104];
} LayoutNode;

typedef struct SlotLayout {
    int state;
    int mode;
    u8 pad8[0xf0];
    int timer;
    u8 padFC[0x10];
    int step;
    u8 pad110[0x88];
    s16 frameCount;
    u8 pad19A[0x1e];
    LayoutNode cursors[2];
} SlotLayout;

extern SlotLayout *data_ov001_020a04ec;
extern int *func_01ffb2f8(void *node, int animation, int frame);

BOOL StartSlotLayoutAnimation(int mode, int frameCount) {
    SlotLayout *layout = data_ov001_020a04ec;
    void *node;
    int offset;

    if (layout != NULL) {
        layout->mode = mode;
        layout->step = 0;
        layout->frameCount = frameCount;
        layout->timer = 0;
        if (mode != 0) {
            if (mode <= 2) {
                node = &layout->cursors[mode - 1];
            } else {
                if (mode == 3) {
                    offset = 0x3d8;
                } else if (mode == 4) {
                    offset = 0x600;
                } else {
                    goto done;
                }
                node = (u8 *)layout + offset;
            }
            func_01ffb2f8(node, 3, (frameCount - 1) << 12);
        }
    }
done:
    return layout != NULL;
}
