#include "nitro/types.h"

typedef struct CornerOffset {
    s32 x;
    s32 y;
} CornerOffset;

typedef struct CornerOffsets {
    CornerOffset corners[4];
} CornerOffsets;

typedef struct CornerItem {
    u8 pad_00[0x10];
    CornerOffset position;
    u8 pad_18[0x18];
} CornerItem;

extern const CornerOffsets data_ov001_0209dac4;
extern void func_ov001_0206ad28(void *list);

void PlaceCornerItems(CornerItem *items, s32 distance, const s32 *center)
{
    CornerOffsets table = data_ov001_0209dac4;
    CornerOffset *offsets = table.corners;
    CornerOffset position;
    int i;

    for (i = 0; i < 4; i++) {
        if (offsets[i].x > 0) {
            position.x = distance;
        } else {
            position.x = -distance;
        }
        if (offsets[i].y > 0) {
            position.y = distance;
        } else {
            position.y = -distance;
        }
        position.x += center[0] + offsets[i].x;
        position.y += center[1] + offsets[i].y;
        items[i].position = position;
        func_ov001_0206ad28(&items[i]);
    }
}
