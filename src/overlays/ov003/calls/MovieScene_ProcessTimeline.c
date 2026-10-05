#include "nitro/types.h"

typedef struct MovieEvent {
    u32 triggerTime;
    u16 handlerIndex;
    u8 payload[6];
} MovieEvent;

typedef struct MovieScene {
    u16 unk_00;
    u16 flags;
    u8 pad_004[0x8c8];
    int brightness;
    u8 pad_8d0[0x14c];
    int eventIndex;
} MovieScene;

typedef BOOL (*MovieEventHandler)(MovieScene *scene, u32 time, MovieEvent *event);

extern MovieEvent data_ov003_02065134[];
extern MovieEventHandler gMovieEventHandlers[];
extern void SetBrightnessAndSyncMain(int brightness);

void MovieScene_ProcessTimeline(MovieScene *scene, u32 time)
{
    MovieEvent *event = &data_ov003_02065134[scene->eventIndex];

    if (scene->flags & 4) {
        return;
    }
    while (event->triggerTime <= time) {
        if (!gMovieEventHandlers[event->handlerIndex](scene, time, event)) {
            break;
        }
        scene->eventIndex++;
        event++;
    }
    SetBrightnessAndSyncMain(scene->brightness);
}
