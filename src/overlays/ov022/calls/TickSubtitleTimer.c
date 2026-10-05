#include "nitro/types.h"

typedef struct {
    u32 unk_00;
    u32 unk_04;
    void *subtitles;
} MovieGlobals;

typedef struct {
    u8 pad_00[0x58];
    int subtitlesDone;
} MovieFileBank;

extern MovieGlobals data_ov022_020b7da8;
extern MovieFileBank data_ov022_020b7db4;

extern int func_ov022_020a8750(void *timer);

int TickSubtitleTimer(void) {
    int done = func_ov022_020a8750(data_ov022_020b7da8.subtitles);

    if (done) {
        data_ov022_020b7db4.subtitlesDone = 1;
    }
    return done;
}
