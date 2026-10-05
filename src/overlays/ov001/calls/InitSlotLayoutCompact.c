#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct SlotPoint {
    fx32 x;
    fx32 y;
} SlotPoint;

typedef struct SlotLayout {
    int state;
    u8 pad4[0xec];
    int timer;
    u8 padF4[0x20];
    SlotPoint points[5];
    u8 pad13C[0x14];
    u8 mode;
    u8 cursor;
    u8 scroll;
} SlotLayout;

extern SlotLayout *data_ov001_020a04ec;

BOOL InitSlotLayoutCompact(u8 mode) {
    SlotLayout *layout = data_ov001_020a04ec;
    int i;
    int offset;

    if (layout != NULL) {
        offset = 0;
        for (i = 0; i < 4; i++) {
            layout->points[i].x = (offset << 12) + 0xb000;
            offset += 13;
            layout->points[i].y = 0x13000;
        }
        layout->mode = mode;
        layout->scroll = 0;
        layout->cursor = 0;
        layout->state = 5;
        layout->timer = 0;
    }
    return layout != NULL;
}
