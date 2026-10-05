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
    int first;
    int second;
} SlotLayout;

extern SlotLayout *data_ov001_020a04ec;

BOOL InitSlotLayout(int first, int second) {
    SlotLayout *layout = data_ov001_020a04ec;
    int i;
    int offset;

    if (layout != NULL) {
        offset = 0;
        for (i = 0; i < 5; i++) {
            layout->points[i].x = (offset << 12) + 0xb000;
            offset += 13;
            layout->points[i].y = 0x13000;
        }
        layout->first = first;
        layout->second = second;
        layout->state = 4;
        layout->timer = 0;
    }
    return layout != NULL;
}
