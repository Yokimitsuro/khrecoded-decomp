#include "nitro/types.h"

typedef struct ChannelState {
    u8 unknown_00[0x20];
    u8 levelA[3];
    u8 levelB[3];
    u8 levelC[3];
    u8 levelD[3];
    u8 levelE[3];
    u8 levelF[3];
    u8 unknown_32[2];
    u16 value[3];
} ChannelState;

typedef struct SoundWork {
    void *unknown_00;
    ChannelState *channels;
} SoundWork;

extern SoundWork data_ov035_020bc508;
extern int RemapMovieMenuValue(ChannelState *state, int id);
extern void DrawDigitRow(ChannelState *state, int slot, int value);

void UpdateChannelLevel(int slot, int ratio) {
    u8 previous;
    u8 level;
    u8 *peaks;
    u8 *floors;
    ChannelState *state = data_ov035_020bc508.channels;

    slot = RemapMovieMenuValue(state, slot);
    level = (ratio * 24) / state->value[slot];

    if (ratio != 0 && level == 0) {
        level = 1;
    }
    if (level > state->levelB[slot]) {
        state->levelB[slot] = level;
        state->levelC[slot] = level;
    }
    peaks = state->levelE;
    previous = peaks[slot];
    if (level < previous) {
        floors = state->levelA;
        if (state->levelF[slot] <= floors[slot]) {
            state->levelC[slot] = previous;
            state->levelF[slot] = (state->levelD[slot] = state->levelE[slot]) + 8;
        }
        peaks[slot] = level;
        floors[slot] = level;
        state->levelB[slot] = level;
    }
    DrawDigitRow(state, slot, ratio);
}
