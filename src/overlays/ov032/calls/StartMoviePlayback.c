#include "nitro/types.h"

typedef struct {
    s16 frame;
    s16 width;
    s16 height;
    u16 flags;
    u8 mode;
    u8 pad_09[0x27];
    int elapsed;
} MovieState;

typedef struct {
    s8 mode;
    s8 frame;
    s16 width;
    s16 height;
} MovieParams;

extern struct { int reserved; MovieState *state; } data_ov032_020c0080;
extern u8 data_020608c8;
extern int func_ov001_020645c8(int flag);
extern void SetupFlaggedSelectionRecords(void);
extern void FlushPendingFieldUpdate(void);
extern BOOL QueueFieldUpdate(int request);

void StartMoviePlayback(MovieParams *params)
{
    u8 previous;

    data_ov032_020c0080.state->width = params->width;
    data_ov032_020c0080.state->height = params->height;
    data_ov032_020c0080.state->frame = params->frame;
    data_ov032_020c0080.state->flags = 3;
    data_ov032_020c0080.state->flags |= 0x20;
    data_ov032_020c0080.state->mode = params->mode;
    data_ov032_020c0080.state->elapsed = 0;
    if (func_ov001_020645c8(0x3609) || func_ov001_020645c8(0x360a)) {
        previous = data_020608c8;
        SetupFlaggedSelectionRecords();
        if (previous != data_020608c8) {
            FlushPendingFieldUpdate();
            QueueFieldUpdate(0);
        }
    }
}
