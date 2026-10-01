typedef unsigned int u32;
typedef int BOOL;

typedef struct NNSSndStrmPlayer {
    unsigned char reserved0[0xac];
    u32 fileOffset;
    unsigned char info[0x40];
} NNSSndStrmPlayer;

extern void MI_CpuCopy8(const void *source, void *destination, u32 size);
extern void *NNS_SndArcGetFileAddress(u32 fileId);

BOOL OpenMemoryStream(NNSSndStrmPlayer *player, u32 fileId)
{
    player->fileOffset = (u32)NNS_SndArcGetFileAddress(fileId);
    MI_CpuCopy8((const void *)player->fileOffset, &player->info, sizeof(player->info));
    return 1;
}