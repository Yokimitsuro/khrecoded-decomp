#include "nitro/types.h"

typedef struct {
    s32 state;
    u8 pad_004[0xec];
    s32 elapsedA;
    s32 elapsedB;
    u8 pad_0f8[0x1c];
    s32 duration;
    s32 progress;
    s32 tickA;
    s32 tickB;
    s32 columnX[4];
    s32 baseX;
    u8 pad_138;
    u8 digitCount;
    u8 pad_13a[2];
    s32 userData;
    u8 visible : 1;
    u8 enabled : 1;
    u8 paused : 1;
    u8 finished : 1;
    u8 pad_bit4 : 1;
    u8 blinking : 1;
    u8 pad_bits : 2;
} CountdownTimer;

extern CountdownTimer *data_ov001_020a04ec;

BOOL StartCountdownTimer(int seconds, s32 userData)
{
    CountdownTimer *timer = data_ov001_020a04ec;

    if (timer != 0) {
        int i;
        s32 x = 0x6800;
        for (i = 0; i < 4; i++) {
            timer->columnX[i] = x;
            if ((u32)i <= 1) {
                x += 0x9800;
            } else {
                x += 0xd000;
            }
        }
        timer->baseX = 0x33800;
        timer->duration = seconds * 1000;
        timer->progress = 0;
        timer->enabled = 1;
        timer->visible = 0;
        timer->paused = 0;
        timer->finished = 0;
        timer->tickA = 0;
        timer->tickB = 0;
        timer->userData = userData;
        timer->blinking = 0;
        timer->digitCount = 10;
        timer->state = 1;
        timer->elapsedB = 0;
        timer->elapsedA = 0;
    }
    return timer != 0;
}

