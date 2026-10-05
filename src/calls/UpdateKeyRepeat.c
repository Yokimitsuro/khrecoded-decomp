#include "nitro/types.h"

typedef struct KeyRepeatState {
    u16 repeatMask;
    u16 delayFrames;
    u16 intervalFrames;
    u16 repeatCounts[10];
} KeyRepeatState;

extern u16 data_020604fc;
extern u16 data_02060500;
extern u32 data_02060504[];
extern const u16 data_02055a2c[];
extern const u16 data_02055a18[];

extern u32 func_01ff80d4(void);
extern u32 _u32_div_f(u32 dividend, u32 divisor);

void UpdateKeyRepeat(KeyRepeatState *state)
{
    int keyIndex;
    u32 now;
    u16 mask;
    u32 elapsed;

    keyIndex = 0;
    state->repeatMask = 0;
    now = func_01ff80d4();
    do {
        mask = data_02055a2c[keyIndex];
        if (data_020604fc & mask) {
            if (data_02060500 & mask) {
                state->repeatMask |= mask;
                state->repeatCounts[keyIndex] = 0;
            } else if ((elapsed = now - data_02060504[data_02055a18[keyIndex]]) >= state->delayFrames * 2
                       && (elapsed -= state->delayFrames * 2) >= state->repeatCounts[keyIndex] * (state->intervalFrames * 2)) {
                state->repeatMask |= mask;
                state->repeatCounts[keyIndex] = _u32_div_f(elapsed, state->intervalFrames * 2) + 1;
            }
        }
        keyIndex++;
    } while (keyIndex < 10);
}
