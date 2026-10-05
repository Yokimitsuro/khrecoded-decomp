#include "nitro/types.h"

typedef struct InputEvent {
    u8 kind;
    s8 button;
    s16 x;
    s16 y;
} InputEvent;

typedef struct PanelWork {
    s16 button;
    s16 x;
    s16 y;
    s16 state;
    s32 timer;
} PanelWork;

typedef struct PanelContext {
    u32 unk_00;
    PanelWork *work;
} PanelContext;

extern PanelContext data_ov036_020c3940;

void RecordPanelInputEvent(const InputEvent *event)
{
    data_ov036_020c3940.work->x = event->x;
    data_ov036_020c3940.work->y = event->y;
    data_ov036_020c3940.work->button = event->button;
    data_ov036_020c3940.work->state = 3;
    data_ov036_020c3940.work->timer = 0;
}
