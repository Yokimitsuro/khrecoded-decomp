#include "nitro/types.h"

typedef struct TrackState {
    s16 defaultMain;
    s16 defaultSub;
    s16 main;
    s16 sub;
    u32 unk8;
    u32 mode : 2;
    u32 unk2 : 4;
    u32 subOverride : 1;
    u32 unk7 : 25;
} TrackState;

typedef struct FieldContext {
    u8 pad[0x208];
    TrackState track;
    u8 pad218[0x268c];
    u8 trackParam;
} FieldContext;

extern FieldContext *data_ov001_020a0480;
extern void SetPendingFieldValue(int arg);

void ConfigureFieldTracks(int mainId, int subId, u8 param, int mode) {
    FieldContext *context = data_ov001_020a0480;
    TrackState *track = &context->track;

    if (mainId != 0) {
        if (mainId < 0) {
            track->main = track->defaultMain;
        } else {
            track->main = mainId;
        }
        SetPendingFieldValue(1);
    }
    if (subId == -1) {
        track->sub = track->defaultSub;
    } else {
        if (subId < 0) {
            track->subOverride = 1;
            track->sub = subId;
        } else {
            track->sub = subId;
        }
    }
    if (mode >= 0) {
        track->mode = mode;
    }
    context->trackParam = param;
}
