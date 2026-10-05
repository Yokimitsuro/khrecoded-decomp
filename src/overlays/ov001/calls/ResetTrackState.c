#include "nitro/types.h"

typedef struct TrackState {
    u8 phase;
    u8 trackId;
    u16 timer;
} TrackState;

typedef struct Session {
    u8 pad_0000[0x27f8];
    TrackState track;
} Session;

extern Session *data_ov001_020a0480;
extern u32 SetScriptBusyFlag(u32 value);

void ResetTrackState(void) {
    Session *session = data_ov001_020a0480;
    TrackState *track = &session->track;
    SetScriptBusyFlag(-1);
    track->timer = 0;
    track->phase = 0;
}
