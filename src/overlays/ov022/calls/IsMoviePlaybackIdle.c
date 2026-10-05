#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x8b5];
    u8 playing;
} MoviePlayer;

extern MoviePlayer *data_ov022_020b7da0;

BOOL IsMoviePlaybackIdle(void) {
    return data_ov022_020b7da0->playing == 0;
}
