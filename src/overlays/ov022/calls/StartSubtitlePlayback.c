#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x8b0];
    int state;
    u8 pad_8B4[4];
    int pendingFrame;
} MoviePlayer;

extern MoviePlayer *data_ov022_020b7da0;

extern void ActivateSubtitleStream(void);

void StartSubtitlePlayback(void) {
    MoviePlayer *player = data_ov022_020b7da0;

    player->pendingFrame = -1;
    player->state = 2;
    ActivateSubtitleStream();
}
