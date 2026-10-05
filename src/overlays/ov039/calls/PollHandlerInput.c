#include "nitro/types.h"

typedef struct Ov039State {
    u8 pad_0000[0xc998];
    void *primaryWork;
    void *secondaryWork;
    u8 pad_c9a0[0x70];
    BOOL inputEnabled;
    u8 pad_ca14[4];
    BOOL primaryActive;
    BOOL secondaryActive;
    u16 buttonState;
    u8 pad_ca22[0x1a];
    BOOL inputBlocked;
    u8 pad_ca40[0xa];
    u16 inputSource;
} Ov039State;

extern Ov039State *data_ov039_020bea20;
extern u16 data_02060500;

extern u16 ReadHalfword(const u16 *source);
extern int func_ov039_020bd0a4(void *primary, void *secondary);
extern int func_ov039_020bd11c(void *primary, void *secondary);
extern int func_ov039_020bd194(void *primary, void *secondary);
extern int func_ov039_020bd20c(void *primary, void *secondary);
extern int func_ov039_020bd284(void *primary, void *secondary);
extern int func_ov039_020bd2fc(void *primary, void *secondary);
extern int func_ov039_020bd374(void *primary, void *secondary);
extern int func_ov039_020bd3ec(void *primary, void *secondary);
extern int func_ov039_020bd464(void *primary, void *secondary);
extern int func_ov039_020bd4dc(void *primary, void *secondary);
extern int func_ov039_020bd554(void *primary, void *secondary);
extern int func_ov039_020bd5cc(void *primary, void *secondary);

void PollHandlerInput(void)
{
    Ov039State *state = data_ov039_020bea20;
    void *primary = state->primaryActive ? state->primaryWork : NULL;
    void *secondary = state->secondaryActive ? state->secondaryWork : NULL;

    if (state->inputEnabled == 0) {
        return;
    }
    if (state->inputBlocked == 0) {
        if ((ReadHalfword(&state->inputSource) & 0x40) && func_ov039_020bd0a4(primary, secondary)) {
            return;
        }
        if ((ReadHalfword(&state->inputSource) & 0x80) && func_ov039_020bd11c(primary, secondary)) {
            return;
        }
        if ((ReadHalfword(&state->inputSource) & 0x20) && func_ov039_020bd194(primary, secondary)) {
            return;
        }
        if ((ReadHalfword(&state->inputSource) & 0x10) && func_ov039_020bd20c(primary, secondary)) {
            return;
        }
        if ((data_02060500 & 0x1) && func_ov039_020bd284(primary, secondary)) {
            return;
        }
        if ((data_02060500 & 0x2) && func_ov039_020bd2fc(primary, secondary)) {
            return;
        }
        if ((data_02060500 & 0x400) && func_ov039_020bd374(primary, secondary)) {
            return;
        }
        if ((data_02060500 & 0x800) && func_ov039_020bd3ec(primary, secondary)) {
            return;
        }
        if ((data_02060500 & 0x200) && func_ov039_020bd464(primary, secondary)) {
            return;
        }
        if ((data_02060500 & 0x100) && func_ov039_020bd4dc(primary, secondary)) {
            return;
        }
        if ((data_02060500 & 0x4) && func_ov039_020bd554(primary, secondary)) {
            return;
        }
        if ((data_02060500 & 0x8) && func_ov039_020bd5cc(primary, secondary)) {
            return;
        }
    }
    state->buttonState = (data_02060500 & 0x2f0f) | (ReadHalfword(&state->inputSource) & 0xf0);
}
