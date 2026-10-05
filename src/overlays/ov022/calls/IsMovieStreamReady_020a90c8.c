#include "nitro/types.h"

typedef struct MovieStream {
    u8 pad_00[0x58];
    s32 entryIndex;
    u8 pad_5C[0x4];
    s32 mode;
    u8 pad_64[0x4];
    s8 *readyFlags;
} MovieStream;

BOOL IsMovieStreamReady_020a90c8(MovieStream *stream)
{
    switch (stream->mode) {
    case 0:
        return stream->readyFlags[stream->entryIndex] != 0;
    case 1:
    case 2:
    case 3:
    case 4:
        return TRUE;
    default:
        return FALSE;
    }
}
