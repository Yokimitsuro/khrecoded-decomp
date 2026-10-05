#include "nitro/types.h"

typedef struct {
    s32 x;
    s32 y;
} Point2D;

typedef struct {
    u8 pad_00[0x10];
    Point2D pos;
    u8 pad_18[0xd];
    u8 visible;
    u8 pad_26[2];
    u16 angle;
    u8 pad_2a[6];
} PairedObject;

extern s32 *data_ov001_020a04a4;
extern void func_ov001_0206ad28(void *list);

void SetupMirroredObjectPair(PairedObject *objects, Point2D *pos)
{
    BOOL dual = TRUE;

    if ((*data_ov001_020a04a4 & 2) <= 0) {
        dual = FALSE;
    }
    objects[0].pos = *pos;
    objects[1].pos = *pos;
    objects[0].angle -= 500;
    if (dual) {
        objects[0].visible = TRUE;
        objects[1].angle += 500;
    } else {
        objects[0].visible = FALSE;
    }
    func_ov001_0206ad28(&objects[0]);
    if (dual) {
        func_ov001_0206ad28(&objects[1]);
    }
}
