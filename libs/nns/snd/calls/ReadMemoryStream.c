typedef signed int s32;
typedef unsigned int u32;
typedef unsigned char u8;

typedef struct NNSSndStrmPlayer {
    unsigned char reserved0[0xac];
    u32 fileOffset;
} NNSSndStrmPlayer;

extern void MI_CpuCopy8(const void *source, void *destination, u32 size);

s32 ReadMemoryStream(NNSSndStrmPlayer *player, void *destination, u32 size, u32 offset)
{
    const u8 *source = (const u8 *)player->fileOffset;
    MI_CpuCopy8(source + offset, destination, size);
    return (s32)size;
}