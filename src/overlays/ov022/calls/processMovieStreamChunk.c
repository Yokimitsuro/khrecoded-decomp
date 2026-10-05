typedef unsigned int u32;
typedef unsigned short u16;
enum MovieContextByteOffset {
    MOVIE_CONTEXT_CHUNK_TYPE = 0x1c,
    MOVIE_CONTEXT_STREAM_CURSOR_POINTER = 0x34,
    MOVIE_CONTEXT_CHUNK_SLOT_TABLE = 0x58,
    MOVIE_CONTEXT_READ_LIMIT = 0xc8,
    MOVIE_CONTEXT_PENDING_CHUNK_COUNT = 0xcc,
    MOVIE_CONTEXT_ACTIVE_SLOT_INDEX = 0xd0,
    MOVIE_CONTEXT_CHUNK_STATE = 0xa4,
    MOVIE_CONTEXT_SLOT_COUNT = 0x1e
};
struct MovieChunkRecord {
    int chunkStreamAddress;
    int outputBuffer;
    unsigned char unknown_008[0x14f0];
};
extern int func_ov022_020aac54(int chunkRecord);
extern void func_ov022_020ab614(int chunkRecord);
extern void func_ov022_020aaae8(int chunkRecord, int chunkAddress);
extern void decodeMovieAdpcmSamples(int chunkRecord, int chunkAddress, int size, int outputBuffer);
extern void MIi_CpuCopy16(int source, int outputBuffer, int size, int option);
int processMovieStreamChunk(int movieContext, int outputBuffer, int unusedArgument, int copyOption)
{
    u16 chunkType;
    u32 frameSlot;
    if (*(int *)(movieContext + MOVIE_CONTEXT_PENDING_CHUNK_COUNT) == *(int *)(movieContext + MOVIE_CONTEXT_READ_LIMIT)) {
        return 0;
    }
    chunkType = *(short *)(movieContext + MOVIE_CONTEXT_CHUNK_TYPE);
    if (chunkType == 0) {
        return 0;
    }
    if (chunkType == 1) {
        ((struct MovieChunkRecord *)*(int *)(movieContext + MOVIE_CONTEXT_CHUNK_SLOT_TABLE))[*(int *)(movieContext + MOVIE_CONTEXT_ACTIVE_SLOT_INDEX)].chunkStreamAddress =
            **(int **)(movieContext + MOVIE_CONTEXT_STREAM_CURSOR_POINTER);
        ((struct MovieChunkRecord *)*(int *)(movieContext + MOVIE_CONTEXT_CHUNK_SLOT_TABLE))[*(int *)(movieContext + MOVIE_CONTEXT_ACTIVE_SLOT_INDEX)].outputBuffer = outputBuffer;
        **(int **)(movieContext + MOVIE_CONTEXT_STREAM_CURSOR_POINTER) += func_ov022_020aac54(*(int *)(movieContext + MOVIE_CONTEXT_ACTIVE_SLOT_INDEX) * 0x14f8 + *(int *)(movieContext + MOVIE_CONTEXT_CHUNK_SLOT_TABLE));
    } else if (chunkType == 2) {
        ((struct MovieChunkRecord *)*(int *)(movieContext + MOVIE_CONTEXT_CHUNK_SLOT_TABLE))[*(int *)(movieContext + MOVIE_CONTEXT_ACTIVE_SLOT_INDEX)].chunkStreamAddress =
            **(int **)(movieContext + MOVIE_CONTEXT_STREAM_CURSOR_POINTER);
        ((struct MovieChunkRecord *)*(int *)(movieContext + MOVIE_CONTEXT_CHUNK_SLOT_TABLE))[*(int *)(movieContext + MOVIE_CONTEXT_ACTIVE_SLOT_INDEX)].outputBuffer = outputBuffer;
        func_ov022_020ab614(*(int *)(movieContext + MOVIE_CONTEXT_ACTIVE_SLOT_INDEX) * 0x14f8 + *(int *)(movieContext + MOVIE_CONTEXT_CHUNK_SLOT_TABLE));
        **(int **)(movieContext + MOVIE_CONTEXT_STREAM_CURSOR_POINTER) += 0x28;
    } else if (chunkType == 3) {
        if (*(int *)(movieContext + MOVIE_CONTEXT_CHUNK_STATE) == 1) {
            func_ov022_020aaae8(*(int *)(movieContext + MOVIE_CONTEXT_ACTIVE_SLOT_INDEX) * 0x14f8 + *(int *)(movieContext + MOVIE_CONTEXT_CHUNK_SLOT_TABLE),
                                **(int **)(movieContext + MOVIE_CONTEXT_STREAM_CURSOR_POINTER));
            **(int **)(movieContext + MOVIE_CONTEXT_STREAM_CURSOR_POINTER) += 4;
        }
        decodeMovieAdpcmSamples(*(int *)(movieContext + MOVIE_CONTEXT_ACTIVE_SLOT_INDEX) * 0x14f8 + *(int *)(movieContext + MOVIE_CONTEXT_CHUNK_SLOT_TABLE),
                            **(int **)(movieContext + MOVIE_CONTEXT_STREAM_CURSOR_POINTER), 0x80, outputBuffer);
        **(int **)(movieContext + MOVIE_CONTEXT_STREAM_CURSOR_POINTER) += 0x80;
    } else {
        MIi_CpuCopy16(**(int **)(movieContext + MOVIE_CONTEXT_STREAM_CURSOR_POINTER), outputBuffer, 0x200, copyOption);
        **(int **)(movieContext + MOVIE_CONTEXT_STREAM_CURSOR_POINTER) += 0x200;
    }
    frameSlot = *(u32 *)(movieContext + MOVIE_CONTEXT_ACTIVE_SLOT_INDEX) + 1;
    *(u32 *)(movieContext + MOVIE_CONTEXT_ACTIVE_SLOT_INDEX) = frameSlot;
    if (frameSlot == *(u16 *)(movieContext + MOVIE_CONTEXT_SLOT_COUNT)) {
        *(u32 *)(movieContext + MOVIE_CONTEXT_ACTIVE_SLOT_INDEX) = 0;
        *(u32 *)(movieContext + MOVIE_CONTEXT_CHUNK_STATE) = 0;
    }
    *(int *)(movieContext + MOVIE_CONTEXT_PENDING_CHUNK_COUNT) = *(int *)(movieContext + MOVIE_CONTEXT_PENDING_CHUNK_COUNT) + 1;
    return 1;
}
