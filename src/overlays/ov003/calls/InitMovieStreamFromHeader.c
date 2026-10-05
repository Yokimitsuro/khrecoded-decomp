#include "nitro/types.h"

typedef struct MovieHeader {
    u16 unk_00;
    u16 unk_02;
    u16 blockWidth;
    u16 blockHeight;
    u16 unk_08;
    u16 unk_0A;
    u16 flags;
    u16 cropLeft;
    u16 cropRight;
    u16 cropTop;
    u16 cropBottom;
} MovieHeader;

typedef struct MovieHeaderCopy {
    u16 unk_00;
    u16 unk_02;
    u16 blockWidth;
    u16 blockHeight;
    u16 unk_08;
    u16 unk_0A;
    u16 unk_0C;
    u16 flags;
} MovieHeaderCopy;

typedef struct MovieStream {
    u8 pad_00[0x34];
    u32 width;
    u32 height;
    u16 cropLeft;
    u16 cropRight;
    u16 cropTop;
    u16 cropBottom;
    s32 unk_44;
    u32 flags;
    s32 unk_4C;
    s32 unk_50;
    s32 active;
    s32 entryIndex;
    u8 pad_5C[0x4];
    s32 mode;
    s32 unk_64;
    s8 *readyFlags;
    s32 slots[4];
    s32 unk_7C;
} MovieStream;

void InitMovieStreamFromHeader(MovieStream *stream, MovieHeaderCopy *copy, MovieHeader *header)
{
    int slotIndex;

    copy->unk_00 = header->unk_00;
    copy->unk_02 = header->unk_02;
    copy->blockWidth = header->blockWidth;
    copy->blockHeight = header->blockHeight;
    copy->unk_08 = header->unk_08;
    copy->unk_0A = header->unk_0A;
    copy->unk_0C = 0;
    copy->flags = header->flags;

    stream->active = 1;
    stream->entryIndex = 0;
    stream->readyFlags = NULL;
    stream->mode = 0;

    stream->flags = header->flags;
    stream->cropLeft = header->cropLeft;
    stream->cropRight = header->cropRight;
    stream->cropTop = header->cropTop;
    stream->cropBottom = header->cropBottom;

    stream->width = (header->blockWidth * 8 - stream->cropLeft) - stream->cropRight;
    stream->height = (header->blockHeight * 8 - stream->cropTop) - stream->cropBottom;

    stream->unk_64 = 0;
    stream->unk_4C = 0;
    stream->unk_50 = 0;
    stream->unk_7C = 0;

    slotIndex = 0;
    do {
        stream->slots[slotIndex] = 0;
        slotIndex++;
    } while (slotIndex < 4);

    stream->unk_44 = 0;
}
