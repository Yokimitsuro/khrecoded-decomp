#include "nitro/types.h"

typedef struct {
    u8 pad_00[0xe];
    u16 kind;
    u16 active;
    u8 pad_12[0x1c8 - 0x12];
} StageEvent;

typedef struct {
    u8 pad_00[0x210];
    StageEvent *events;
    u8 pad_214[0x18dee - 0x214];
    u16 eventCount;
    u8 pad_18df0[4];
    u16 eventCursor;
} StageManager;

extern StageManager *data_ov001_020a0528;

void SeekFirstActiveStageEvent(void)
{
    u16 index;
    StageEvent *event;

    index = 0;
    data_ov001_020a0528->eventCursor = 0;
    for (; index < data_ov001_020a0528->eventCount; index++) {
        data_ov001_020a0528->eventCursor = index;
        event = &data_ov001_020a0528->events[index];
        if (event->active != 0) {
            return;
        }
        if (event->kind == 99) {
            return;
        }
    }
}
