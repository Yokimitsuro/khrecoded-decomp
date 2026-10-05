#include "nitro/types.h"

typedef struct {
    s32 dataOffset;
    s32 pad_04;
    s32 trackStarts[11];
} SequenceFile;

typedef struct Sequencer {
    u16 header[4];
    u8 *base;
    void *buffer;
    SequenceFile *file;
    s32 track;
    s32 rateA;
    s32 rateB;
    u8 pad20[0x50];
    s32 trackStarts[11];
    u32 cursorBits : 31;
    u32 ownsBuffer : 1;
    u16 id;
    u8 pad_a2[6];
} Sequencer;

extern void FreeOwnedBuffer(Sequencer *sequencer);
extern void MI_CpuFill8(void *dest, u32 value, u32 size);
extern void *AllocFromStageHeap(u32 size);
extern void MI_CpuCopy8(const void *src, void *dst, u32 size);
extern int SelectSequenceTrack(Sequencer *sequencer, int track);

void InitSequencer(Sequencer *sequencer, u16 *header, SequenceFile *file, u8 *end)
{
    u32 size;
    void *copy;
    int i;

    FreeOwnedBuffer(sequencer);
    MI_CpuFill8(sequencer, 0, sizeof(Sequencer));
    sequencer->header[0] = header[0];
    sequencer->header[1] = header[1];
    sequencer->header[2] = header[2];
    sequencer->header[3] = header[3];
    sequencer->cursorBits = 0;
    sequencer->rateA = 0x60;
    sequencer->rateB = 0x60;
    sequencer->track = -1;
    sequencer->file = file;
    sequencer->base = (u8 *)file;
    sequencer->id = header[2];
    size = end - file->dataOffset;
    copy = AllocFromStageHeap(size);
    if (copy == NULL) {
        sequencer->buffer = sequencer->base + sequencer->file->dataOffset;
    } else {
        MI_CpuCopy8(sequencer->base + sequencer->file->dataOffset, copy, size);
        sequencer->buffer = copy;
        sequencer->ownsBuffer = 1;
    }
    for (i = 0; i < 11; i++) {
        sequencer->trackStarts[i] = sequencer->file->trackStarts[i];
    }
    SelectSequenceTrack(sequencer, 0);
}
