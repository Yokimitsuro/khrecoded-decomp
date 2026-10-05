#include "nitro/types.h"

typedef struct {
    u32 words[14];
} PanelSnapshot;

typedef struct {
    PanelSnapshot base;
    u32 pad38;
    int angleX;
    int angleY;
    u32 flags;
} PanelView;

typedef struct {
    PanelSnapshot base;
    u8 pad38[0x1c];
    int angle;
} Panel;

extern Panel *data_ov044_020d0ec0;

void GetPanelViewEx(int unused0, int unused1, PanelView *view)
{
    Panel *panel = data_ov044_020d0ec0;

    view->base = panel->base;
    view->angleX = -panel->angle;
    view->angleY = -panel->angle;
    view->flags = 0;
}
