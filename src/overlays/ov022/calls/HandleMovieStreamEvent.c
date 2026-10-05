#include "nitro/types.h"

typedef struct MovieStream {
    u8 pad_00[0x58];
    s32 entryIndex;
    s32 stateCounter;
    s32 mode;
} MovieStream;

extern void ResetSubtitleLine(MovieStream *stream);
extern int advanceMovieStreamWindow_020a8a98(MovieStream *stream);

BOOL HandleMovieStreamEvent(MovieStream *stream, int event)
{
    s32 *counter;

    switch (stream->mode) {
    case 0:
        counter = &stream->entryIndex;
        break;
    case 1:
    case 2:
    case 3:
    case 4:
        counter = &stream->stateCounter;
        break;
    }

    switch (event) {
    case 1:
        ResetSubtitleLine(stream);
        break;
    case 3:
        (*counter)++;
        break;
    case 8:
        stream->mode = 1;
        stream->stateCounter = 0;
        break;
    case 9:
        stream->mode = 2;
        stream->stateCounter = 0;
        break;
    case 11:
        stream->mode = 3;
        stream->stateCounter = 0;
        break;
    case 12:
        stream->mode = 4;
        stream->stateCounter = 0;
        break;
    case 10:
        advanceMovieStreamWindow_020a8a98(stream);
        break;
    }
    return TRUE;
}
