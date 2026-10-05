#include "nitro/types.h"

typedef struct StageEvent {
    u8 pad_00[6];
    u16 flagBits : 9;
    u16 isScriptEvent : 1;
    u16 flagHigh : 6;
    u8 pad_08[0x10 - 0x8];
    u16 active;
    u8 pad_12[0x1b7 - 0x12];
    u8 scriptKind : 2;
    u8 scriptArg : 6;
    u8 pad_1b8[0x1c8 - 0x1b8];
} StageEvent;

typedef struct StageManager {
    u8 pad_00000[0x210];
    StageEvent *events;
    u8 pad_00214[0x18dee - 0x214];
    u16 eventCount;
    u8 pad_18df0[0x18df4 - 0x18df0];
    u16 eventCursor;
} StageManager;

extern StageManager *data_ov001_020a0528;
extern u32 func_ov001_0209625c(StageEvent *event, int mode, u32 source, u32 param, u32 extra);
extern BOOL func_ov016_020a6de4(u32 kind, u32 arg, u32 param, u32 extra);

u16 TriggerNextStageEvent(u32 source, u32 param, u32 extra, u16 *outResult)
{
    u16 index;
    StageEvent *event;
    u32 result;

    if (outResult != NULL) {
        *outResult = 0;
    }
    for (index = data_ov001_020a0528->eventCursor; index < data_ov001_020a0528->eventCount; index++) {
        event = &data_ov001_020a0528->events[index];
        if (!event->isScriptEvent) {
            if (event->active != 0) {
                data_ov001_020a0528->eventCursor++;
                result = func_ov001_0209625c(event, 2, source, param, extra);
                if (result != 0) {
                    if (outResult != NULL) {
                        *outResult = result;
                    }
                    return index + 1;
                }
            }
        } else {
            data_ov001_020a0528->eventCursor++;
            if (func_ov016_020a6de4(event->scriptKind, event->scriptArg, param, extra)) {
                return index + 1;
            }
        }
    }
    return 0;
}
