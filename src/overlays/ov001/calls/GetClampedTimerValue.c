#include "nitro/types.h"

typedef struct TimerRecord {
    int limit;
    u8 unk0 : 2;
    u8 countDown : 1;
    u8 unk3 : 5;
} TimerRecord;

typedef struct FieldContext {
    u8 pad[0x29b0];
    TimerRecord timer;
} FieldContext;

extern FieldContext *data_ov001_020a0480;
extern BOOL func_ov001_020645c8(u32 value);
extern u32 func_ov001_02068ea4(s32 index);

int GetClampedTimerValue(void) {
    TimerRecord *timer = &data_ov001_020a0480->timer;
    int value = 0;

    if (func_ov001_020645c8(0x35f0)) {
        if (timer->countDown) {
            value = timer->limit - func_ov001_02068ea4(0);
        } else {
            value = func_ov001_02068ea4(0);
            if (value > 300000) {
                value = 300000;
            }
        }
    }
    if (value < 0) {
        value = 0;
    } else if (value >= 599000) {
        value = 599000;
    }
    return value;
}
