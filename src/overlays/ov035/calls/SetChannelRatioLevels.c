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
    s16 value[3];
} ChannelState;

typedef struct SoundWork {
    void *unknown_00;
    ChannelState *channels;
} SoundWork;

extern SoundWork data_ov035_020bc508;
extern int RemapMovieMenuValue(ChannelState *state, int id);

void SetChannelRatioLevels(int id, int value, int ratio) {
    ChannelState *state = data_ov035_020bc508.channels;
    u8 level = (ratio * 24) / value;
    int slot;

    if (ratio != 0 && level == 0) {
        level = 1;
    }
    slot = RemapMovieMenuValue(state, id);
    state->value[slot] = value;
    state->levelC[slot] = level;
    state->levelE[slot] = level;
    state->levelD[slot] = level;
    state->levelF[slot] = level + 8;
    state->levelA[slot] = level;
    state->levelB[slot] = level;
}
