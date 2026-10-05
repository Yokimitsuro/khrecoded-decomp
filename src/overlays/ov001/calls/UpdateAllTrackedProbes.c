#include "nitro/types.h"

typedef struct {
    u8 data[0x28];
} Track;

typedef struct {
    u32 flags;
    Track main;
    Track extra[3];
} TrackSet;

extern TrackSet *data_ov001_020a04b8;
extern void UpdateTrackedTargetMarker(Track *track, int arg);

void UpdateAllTrackedProbes(int arg) {
    TrackSet *set = data_ov001_020a04b8;
    int i;
    if (set == NULL || (set->flags & 1)) {
        return;
    }
    UpdateTrackedTargetMarker(&set->main, arg);
    for (i = 0; i < 3; i++) {
        UpdateTrackedTargetMarker(&set->extra[i], arg);
    }
}
