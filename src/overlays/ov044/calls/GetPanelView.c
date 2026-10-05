#include "nitro/types.h"

typedef struct {
    u32 words[14];
} PanelSnapshot;

typedef struct {
    PanelSnapshot base;
    u32 flags;
    int angle;
} PanelView;

typedef struct {
    PanelSnapshot base;
    u8 pad38[0x1c];
    int angle;
} Panel;

extern Panel *data_ov044_020d0ec0;

void GetPanelView(PanelView *view)
{
    Panel *panel = data_ov044_020d0ec0;

    view->base = panel->base;
    view->flags = 0;
    view->angle = -panel->angle;
}
