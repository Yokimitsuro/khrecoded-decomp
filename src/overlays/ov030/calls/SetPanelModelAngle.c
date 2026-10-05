#include "nitro/types.h"

typedef struct {
    u32 flags;
    u16 drawFlags;
    u8 pad_06[0x7a];
    u16 angle;
} PanelModel;

typedef struct {
    u8 pad_000[0x230];
    PanelModel *model;
    u8 pad_234[0x528];
    int mode;
} PanelUnit;

void SetPanelModelAngle(PanelUnit *unit, u32 angle) {
    u16 value = angle + 0x8000;
    BOOL clamp = TRUE;
    PanelModel *model;

    if (unit->mode == 0xf) {
        clamp = FALSE;
    }
    if (clamp) {
        if (angle < 0x7fff) {
            value = 0xbfff;
        } else {
            value = 0x4001;
        }
    }
    model = unit->model;
    if (!(model->flags & 0x20)) {
        model->angle = value;
        model->drawFlags |= 0x20;
    }
}
