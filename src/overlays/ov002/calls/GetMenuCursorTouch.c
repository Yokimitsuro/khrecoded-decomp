#include "nitro/types.h"

typedef struct MenuPoint {
    u16 x;
    u16 y;
    u8 pad_04[4];
} MenuPoint;

typedef struct MenuCursor {
    u8 pad_00[4];
    u8 unk_04_b0 : 1;
    u8 touchFlag : 1;
    u8 heldFlag : 1;
    u8 unk_04_b3 : 5;
    u8 pad_05;
    MenuPoint points[3];
    s16 current;
} MenuCursor;

extern MenuCursor *data_ov002_0206c46c;

u32 GetMenuCursorTouch(u32 *out)
{
    if (data_ov002_0206c46c == NULL) {
        return 0;
    }
    if (out != NULL) {
        s16 current = data_ov002_0206c46c->current;
        out[0] = data_ov002_0206c46c->points[current].x;
        out[1] = data_ov002_0206c46c->points[current].y;
    }
    return data_ov002_0206c46c->touchFlag;
}
