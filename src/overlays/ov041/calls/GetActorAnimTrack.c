#include "nitro/types.h"

typedef struct {
    s8 track;
    u8 flags;
} AnimTrackEntry;

typedef struct {
    u8 kind;
} AnimActor;

extern AnimTrackEntry data_ov041_020cf61c[][24];

int GetActorAnimTrack(AnimActor *actor, u8 animId) {
    int track = -1;

    switch (actor->kind) {
    case 0xfd:
    case 0xfe:
    case 0xff:
        track = data_ov041_020cf61c[0xff - actor->kind][animId].track;
        break;
    case 3:
        if (animId == 2) {
            track = 0;
        }
        break;
    case 0x10:
        if (animId == 2) {
            track = 0;
        }
        break;
    default:
        track = -1;
        break;
    }
    return track;
}
